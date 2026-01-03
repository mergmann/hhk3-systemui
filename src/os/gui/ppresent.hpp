#pragma once

#include "pegtypes.hpp"
#include "pwindow.hpp"

struct PegPresentationManager_VFTable : PegWindow_VFTable {
  VFTableFunction<SIGNED, PegMessage *> Dispatch;
};

static_assert(sizeof(PegPresentationManager_VFTable) == 0x210,
              "PegWindow_VFTable has wrong size");

struct PegPresentationManager_Thin : PegWindow_Thin {
public:
  VFT_FORWARD(Dispatch, SIGNED, (PegMessage & mesg), (&mesg))

protected:
  PegThing *mpSavedInputThing;
  PegThing *mpDefaultMessageHandler;
  PegThing *mpDragObject;
  PegThing *mpSavedStackThing[8];

public:
  int mLoadErrorMessageID;

protected:
  PegPoint mLastPointerLocation;
  PegThing *mpInputThing;
  PegThing *mpDefaultInputThing;
  PegThing *mpLastPointerOver;
  PegThing *mpPointerOwners[8];
  PegBitmap *mpWallpaper;
  PEGCHAR *mpScratchPad;
  WORD mwSavedStackSize;
  UCHAR muPointerCaptures;
  UCHAR mbMoveFocusFlag;
  UCHAR mPointerDown;
  UCHAR mFirstStart;
  PegRect rect;

  inline PegPresentationManager_VFTable *vft() {
    return static_cast<PegPresentationManager_VFTable *>(_vft);
  }

  friend class PegWindow;
};

static_assert(sizeof(PegPresentationManager_Thin) == 0xe4,
              "PegPresentationManager_Thin has wrong size");