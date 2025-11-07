#pragma once

#include "pwindow.hpp"

struct PegDecoratedWindow_VFTable : PegWindow_VFTable {};

static_assert(sizeof(PegDecoratedWindow_VFTable) == 0x204,
              "PegDecoratedWindow_VFTable has wrong size");

struct PegDecoratedWindow_Thin : PegWindow_Thin {
  PegThing *mpTitle;
  void *mpMenuBar;
  void *mpStatusBar;
  void *mpToolBar;
};

static_assert(sizeof(PegDecoratedWindow_Thin) == 0x7c,
              "PegDecoratedWindow_Thin has wrong size");

class PegDecoratedWindow : public PegWindow {
public:
  PegDecoratedWindow(PegRect &rect, WORD style = FF_THICK);
  PegDecoratedWindow(WORD style = FF_THICK);

  inline PegDecoratedWindow_Thin *obj() {
    return static_cast<PegDecoratedWindow_Thin *>(_obj);
  }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegDecoratedWindow(PegDecoratedWindow_Thin *obj, size_t vftSize);

private:
  inline PegWindow_VFTable *vftNew() {
    return static_cast<PegWindow_VFTable *>(PegThing::_vftNew);
  }
  inline PegWindow_VFTable *vftOld() {
    return static_cast<PegWindow_VFTable *>(PegThing::_vftOld);
  }
};

extern "C" PegDecoratedWindow_Thin *
PegDecoratedWindow_ctor_0(PegDecoratedWindow_Thin *, PegRect *, WORD);
extern "C" PegDecoratedWindow_Thin *
PegDecoratedWindow_ctor_1(PegDecoratedWindow_Thin *, WORD);
