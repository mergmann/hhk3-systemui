#pragma once
#include "pegtypes.hpp"
#include "util.hpp"
#include <cstddef>

struct PegMessage;
class PegTextThing;

typedef void PegFont;

struct PegTextThing_VFTable : Element_VFTable {
  VFTableFunction<void, bool> _dtor;
  VFTableFunction<void, const PEGCHAR *> DataSet;
  VFTableFunction<void, PegFont *> SetFont;
  VFTableFunction<void *> GetFont;
  VFTableFunction<WORD> TextLength;
};

static_assert(sizeof(PegTextThing_VFTable) == 0x48,
              "PegTextThing_VFTable has wrong size");

struct PegTextThing_Thin : public Element_Thin {
public:
  VFT_FORWARD(DataSet, void, (const PEGCHAR *text), (text))
  VFT_FORWARD(SetFont, void, (PegFont * font), (font))
  VFT_FORWARD(GetFont, void *, (), ())
  VFT_FORWARD(TextLength, WORD, (), ())

protected:
  void *mpFont;
  PEGCHAR *mpText;
  WORD mwStrLen;
  WORD mwBufferLen;
  UCHAR mbCopy;

  void *_vft;

  inline PegTextThing_VFTable *vft() {
    return static_cast<PegTextThing_VFTable *>(_vft);
  }

  friend class PegTextThing;
};

static_assert(sizeof(PegTextThing_Thin) == 0x14,
              "PegTextThing_Thin has wrong size");

class PegTextThing : public Element {
public:
  PegTextThing(const PEGCHAR *text, WORD copy = 0, UCHAR fontIndex = 0);
  PegTextThing(WORD copy = 0, UCHAR fontIndex = 0);

  ~PegTextThing();

  /**
   * @brief Get the underlying ClassPad object
   * @return ClassPad object
   */
  PegTextThing_Thin *obj() { return static_cast<PegTextThing_Thin *>(_obj); }

  virtual void DataSet(const PEGCHAR *text);
  virtual void SetFont(PegFont *font);
  virtual PegFont *GetFont();
  virtual WORD TextLength();

  void *Test() { return vftOld(); }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegTextThing(PegTextThing_Thin *obj, size_t vftSize);

private:
  inline PegTextThing_VFTable *vftNew() {
    return static_cast<PegTextThing_VFTable *>(_vftNew);
  }
  inline PegTextThing_VFTable *vftOld() {
    return static_cast<PegTextThing_VFTable *>(_vftOld);
  }
};

extern "C" PegTextThing_Thin *PegTextThing_ctor_0(PegTextThing_Thin *,
                                                  const PEGCHAR *, WORD, UCHAR);

extern "C" PegTextThing_Thin *PegTextThing_ctor_1(PegTextThing_Thin *, WORD,
                                                  UCHAR);
