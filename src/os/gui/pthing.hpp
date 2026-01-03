#pragma once

#include "pegtypes.hpp"
#include "util.hpp"
#include <cstddef>

struct PegMessage;
class PegScreen_Thin;

struct PegThing_Thin;
struct PegThing_VFTable;

class PegThing;

extern "C" PegThing_Thin *PegThing_ctor_0(PegThing_Thin *, const PegRect *,
                                          WORD, WORD);
extern "C" PegThing_Thin *PegThing_ctor_1(PegThing_Thin *, WORD, WORD);

extern "C" PegScreen_Thin *PegThing_Screen();

struct PegThing_VFTable : Element_VFTable {
  VFTableFunction<void, bool> _dtor;
  VFTableFunction<SIGNED, const PegMessage *> Message;
  VFTableFunction<void> Draw;
  VFTableFunction<void, PegThing_Thin *, BOOL> Add;
  VFTableFunction<void, PegThing_Thin *, BOOL> AddToEnd;
  VFTableFunction<void, PegThing_Thin *> NotifyChildRemoved;
  VFTableFunction<PegThing_Thin *, PegThing_Thin *, BOOL> Remove;
  VFTableFunction<void, PegThing_Thin *> Center;
  VFTableFunction<void> DrawChildren;
  VFTableFunction<void, PegRect> Resize;
  VFTableFunction<PegThing_Thin *, WORD, BOOL> Find;
  VFTableFunction<void, WORD> AddStatus;
  VFTableFunction<void, WORD> RemoveStatus;
  VFTableFunction<WORD> Style_0;
  VFTableFunction<void, WORD> Style_1;
  VFTableFunction<void> InitClient;
  VFTableFunction<void, UCHAR> SendSignal;
  VFTableFunction<void, SIGNED, SIGNED> ParentShift;
  VFT_UNKNOWN_SLOTS(6, 1);
  VFTableFunction<BOOL> HasDefaultFocus;
  VFTableFunction<PegThing_Thin *> GetDefaultFocus;
  VFTableFunction<void, PegThing_Thin *> SetDefaultFocus;
  VFTableFunction<BOOL, PegThing_Thin *, const PEGCHAR *> PasteStringInput;
  VFTableFunction<void, const PegMessage *> RecordMouseMessage;
  VFTableFunction<void, const PegMessage *> RecordKeyMessage;
  VFTableFunction<void, const PegMessage *> RecordSystemMessage;
};

static_assert(sizeof(PegThing_VFTable) == 0x180,
              "PegThing_VFTable has wrong size");

struct PegThing_Thin : public Element_Thin {
public:
  COLORVAL muColors[4];
  PegRect mReal;
  PegRect mClient;
  PegRect mClip;

  /**
   * @brief
   * Process a message from the queue.
   * This is usually overwritten by classes to catch events
   *
   * @param mesg Message to process
   */
  VFT_FORWARD(Message, SIGNED, (PegMessage & mesg), (&mesg))
  VFT_FORWARD(Draw, void, (), ())
  VFT_FORWARD(Add, void, (PegThing_Thin * thing, BOOL draw = TRUE),
              (thing, draw))
  VFT_FORWARD(AddToEnd, void, (PegThing_Thin * thing, BOOL draw = TRUE),
              (thing, draw))
  VFT_FORWARD(NotifyChildRemoved, void, (PegThing_Thin * thing), (thing))
  VFT_FORWARD(Remove, PegThing_Thin *,
              (PegThing_Thin * thing, BOOL draw = TRUE), (thing, draw))
  VFT_FORWARD(Center, void, (PegThing_Thin * thing), (thing))
  VFT_FORWARD(DrawChildren, void, (), ())
  VFT_FORWARD(Resize, void, (PegRect rect), (rect))
  VFT_FORWARD(Find, PegThing_Thin *, (WORD id, BOOL recursive = TRUE),
              (id, recursive))
  VFT_FORWARD(AddStatus, void, (WORD status), (status))
  VFT_FORWARD(RemoveStatus, void, (WORD status), (status))
  VFT_FORWARD_TO(Style, Style_0, WORD, (), ())
  VFT_FORWARD_TO(Style, Style_1, void, (WORD style), (style))
  VFT_FORWARD(InitClient, void, (), ())
  VFT_FORWARD(SendSignal, void, (UCHAR signal), (signal))
  VFT_FORWARD(ParentShift, void, (SIGNED x, SIGNED y), (x, y))
  VFT_FORWARD(HasDefaultFocus, BOOL, (), ())
  VFT_FORWARD(GetDefaultFocus, PegThing_Thin *, (), ())
  VFT_FORWARD(SetDefaultFocus, void, (PegThing_Thin * thing), (thing))
  VFT_FORWARD(PasteStringInput, BOOL,
              (PegThing_Thin * thing, const PEGCHAR *text), (thing, text))
  VFT_FORWARD(RecordMouseMessage, void, (const PegMessage &mesg), (&mesg))
  VFT_FORWARD(RecordKeyMessage, void, (const PegMessage &mesg), (&mesg))
  VFT_FORWARD(RecordSystemMessage, void, (const PegMessage &mesg), (&mesg))

protected:
  UCHAR muType;
  WORD mwStyle;
  WORD mwId;
  WORD mwStatus;
  WORD mwSignalMask;
  PegThing_Thin *mParent;
  PegThing_Thin *mpFirst;
  PegThing_Thin *mpNext;
  PegThing_Thin *mpPrev;

  uint32_t unknown[3];

  void *mpViewportList;

  void *_vft;

  inline PegThing_VFTable *vft() {
    return static_cast<PegThing_VFTable *>(_vft);
  }

  friend PegThing;
};

static_assert(sizeof(PegThing_Thin) == 0x50, "PegThing_Thin has wrong size");

class PegThing : public Element {
public:
  PegThing(const PegRect &Rect, WORD wId, WORD wStyle);
  PegThing(WORD wId, WORD wStyle);

  virtual ~PegThing();

  /**
   * @brief Get the underlying ClassPad object
   * @return ClassPad object
   */
  inline PegThing_Thin *obj() { return static_cast<PegThing_Thin *>(_obj); }

  inline static PegScreen_Thin *Screen() { return PegThing_Screen(); }

  /**
   * @brief
   * Process a message from the queue.
   * This is usually overwritten by classes to catch events
   * @param mesg Message to process
   */
  virtual SIGNED Message(const PegMessage &mesg);
  virtual void Draw();
  virtual void Add(PegThing_Thin *what, BOOL draw = TRUE);
  virtual void AddToEnd(PegThing_Thin *what, BOOL draw = TRUE);
  virtual void NotifyChildRemoved(PegThing_Thin *what);
  virtual PegThing_Thin *Remove(PegThing_Thin *who, BOOL draw = TRUE);
  virtual void Center(PegThing_Thin *who);
  virtual void DrawChildren();
  virtual void Resize(PegRect rect);
  virtual PegThing_Thin *Find(WORD id, BOOL recursive = TRUE);
  virtual void AddStatus(WORD status);
  virtual void RemoveStatus(WORD mask);
  virtual WORD Style();
  virtual void Style(WORD style);
  virtual void InitClient();
  virtual void SendSignal(UCHAR signal);
  virtual void ParentShift(SIGNED x, SIGNED y);
  virtual BOOL HasDefaultFocus();
  virtual PegThing_Thin *GetDefaultFocus();
  virtual void SetDefaultFocus(PegThing_Thin *thing);
  virtual BOOL PasteStringInput(PegThing_Thin *thing, const PEGCHAR *text);
  virtual void RecordMouseMessage(const PegMessage &message);
  virtual void RecordKeyMessage(const PegMessage &message);
  virtual void RecordSystemMessage(const PegMessage &message);

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegThing(PegThing_Thin *obj, size_t vftSize);

private:
  inline PegThing_VFTable *vftNew() {
    return static_cast<PegThing_VFTable *>(_vftNew);
  }
  inline PegThing_VFTable *vftOld() {
    return static_cast<PegThing_VFTable *>(_vftOld);
  }
};
