#pragma once

#include "pegtypes.hpp"
#include "pmessage.hpp"
#include "pthing.hpp"
#include "util.hpp"

struct PegWindow_VFTable : PegThing_VFTable {
  VFTableFunction<SIGNED, bool, bool> ExecuteFlush;
  VFTableFunction<SIGNED> Execute;
  VFTableFunction<void, UCHAR> SetScrollMode;
  VFTableFunction<UCHAR> GetScrollMode;
  VFTableFunction<void, void *> GetVScrollInfo;
  VFTableFunction<void, void *> GetHScrollInfo;
  VFTableFunction<void, BOOL> DrawFrame;
  VFTableFunction<void> MoveFocusToFirstClientChild;
  VFTableFunction<SIGNED, PegMessage &> ExecuteDispatch;
  VFTableFunction<UCHAR, DUMMY, DUMMY, DUMMY, PegPoint> BorderContains;
  VFTableFunction<void, SIGNED, SIGNED, BOOL> MoveClientObjects;
};

static_assert(sizeof(PegWindow_VFTable) == 0x204,
              "PegWindow_VFTable has wrong size");

struct PegWindow_Thin : PegThing_Thin {
public:
  VFT_FORWARD(ExecuteFlush, SIGNED, (bool flush, bool destroy = true),
              (flush, destroy))
  VFT_FORWARD(Execute, SIGNED, (), ())
  VFT_FORWARD(SetScrollMode, void, (UCHAR mode), (mode))
  VFT_FORWARD(GetScrollMode, UCHAR, (), ())
  VFT_FORWARD(GetVScrollInfo, void, (void *info), (info))
  VFT_FORWARD(GetHScrollInfo, void, (void *info), (info))
  VFT_FORWARD(DrawFrame, void, (BOOL fill = TRUE), (fill))
  VFT_FORWARD(MoveFocusToFirstClientChild, void, (), ())

protected:
  VFT_FORWARD(ExecuteDispatch, SIGNED, (PegMessage & mesg), (mesg))
  VFT_FORWARD(MoveClientObjects, void,
              (SIGNED xShift, SIGNED yShift, BOOL draw = TRUE),
              (xShift, yShift, draw))

  // TODO: Check calling convention
  // inline UCHAR BorderContains(PegPoint point) {
  //   return vft()->BorderContains(this, 0, 0, 0, point);
  // }

protected:
  void *mpVScroll;
  void *mpHScroll;
  BOOL mbModal;
  BOOL mvMoveFrame;
  UCHAR muScrollMode;
  UCHAR muMoveMode;
  PegPoint mStartMove;
  PegPoint mMovePoint;

  inline PegWindow_VFTable *vft() {
    return static_cast<PegWindow_VFTable *>(_vft);
  }

  friend class PegWindow;
};

static_assert(sizeof(PegWindow_Thin) == 0x6c, "PegWindow_Thin has wrong size");

class PegWindow : public PegThing {
public:
  PegWindow(PegRect &rect, WORD style = FF_THICK);
  PegWindow(WORD style = FF_THICK);

  inline PegWindow_Thin *obj() { return static_cast<PegWindow_Thin *>(_obj); }

  /// @brief Display the window.
  /// @param flush Flush the message queue.
  /// @param destroy Automatically destroys the underlying ClassPad object after
  /// closing. It does NOT free this wrapper! Using the wrapper after that is a
  /// UAF!
  virtual SIGNED ExecuteFlush(bool flush, bool destroy = true);
  virtual SIGNED Execute(void);
  virtual void SetScrollMode(UCHAR mode);
  virtual UCHAR GetScrollMode();
  virtual void GetVScrollInfo(void *out);
  virtual void GetHScrollInfo(void *out);
  virtual void DrawFrame(BOOL fill = TRUE);
  virtual void MoveFocusToFirstClientChild();

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegWindow(PegWindow_Thin *obj, size_t vftSize);

  virtual SIGNED ExecuteDispatch(PegMessage &mesg);
  // virtual UCHAR BorderContains(PegPoint point);

private:
  inline PegWindow_VFTable *vftNew() {
    return static_cast<PegWindow_VFTable *>(PegThing::_vftNew);
  }
  inline PegWindow_VFTable *vftOld() {
    return static_cast<PegWindow_VFTable *>(PegThing::_vftOld);
  }
};

extern "C" PegWindow_Thin *PegWindow_ctor_0(PegWindow_Thin *, PegRect *, WORD);
extern "C" PegWindow_Thin *PegWindow_ctor_1(PegWindow_Thin *, WORD);
