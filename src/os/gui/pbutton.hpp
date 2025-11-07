#pragma once

#include "pegtypes.hpp"
#include "pfonts.hpp"
#include "pthing.hpp"
#include <cstdint>

struct PegButton_VFTable : PegThing_VFTable {};

static_assert(sizeof(PegButton_VFTable) == 0x180,
              "PegButton_VFTable has wrong size");

struct PegButton_Thin : PegThing_Thin {
  inline PegButton_VFTable *vft() {
    return static_cast<PegButton_VFTable *>(_vft);
  }
};

static_assert(sizeof(PegButton_Thin) == 0x50, "PegButton_Thin has wrong size");

class PegButton : public PegThing {
public:
  PegButton(const PegRect &rect, WORD id = 0, WORD flags = AF_ENABLED);
  PegButton(WORD id = 0, WORD flags = AF_ENABLED);

  inline PegButton_Thin *obj() { return static_cast<PegButton_Thin *>(_obj); }

protected:
  PegButton(PegButton_Thin *inner, size_t vftSize);

private:
  inline PegButton_VFTable *vftNew() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftNew);
  }
  inline PegButton_VFTable *vftOld() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftOld);
  }
};

extern "C" PegButton_Thin *PegButton_ctor_0(PegButton_Thin *, const PegRect *,
                                            WORD, WORD);
extern "C" PegButton_Thin *PegButton_ctor_1(PegButton_Thin *, WORD, WORD);

struct PegTextButton_VFTable : PegThing_VFTable {};

static_assert(sizeof(PegTextButton_VFTable) == 0x180,
              "PegTextButton_VFTable has wrong size");

struct PegTextButton_Thin : PegButton_Thin, PegTextThing_Thin {
  uint32_t unknown_64;

  inline PegTextButton_VFTable *vft() {
    return static_cast<PegTextButton_VFTable *>(PegButton_Thin::_vft);
  }
};

static_assert(sizeof(PegTextButton_Thin) == 0x68,
              "PegTextButton_Thin has wrong size");

class PegTextButton : public PegButton, public PegTextThing {
public:
  PegTextButton(PegRect &rect, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  PegTextButton(SIGNED x, SIGNED y, SIGNED w, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  PegTextButton(SIGNED x, SIGNED y, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  inline PegTextButton_Thin *obj() {
    return static_cast<PegTextButton_Thin *>(PegButton::_obj);
  }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegTextButton(PegTextButton_Thin *obj, size_t vftSize);

private:
  inline PegButton_VFTable *vftNew() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftNew);
  }
  inline PegButton_VFTable *vftOld() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftOld);
  }
};

extern "C" PegTextButton_Thin *PegTextButton_ctor_0(PegTextButton_Thin *,
                                                    PegRect *, const PEGCHAR *,
                                                    WORD, WORD, COLORVAL);

extern "C" PegTextButton_Thin *PegTextButton_ctor_1(PegTextButton_Thin *,
                                                    SIGNED, SIGNED, SIGNED,
                                                    const PEGCHAR *, WORD, WORD,
                                                    COLORVAL);

extern "C" PegTextButton_Thin *PegTextButton_ctor_2(PegTextButton_Thin *,
                                                    SIGNED, SIGNED,
                                                    const PEGCHAR *, WORD, WORD,
                                                    COLORVAL);
