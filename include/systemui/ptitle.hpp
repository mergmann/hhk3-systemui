#pragma once

#include "pfonts.hpp"
#include "pthing.hpp"

struct PegTitle_VFTable : PegThing_VFTable {
  VFT_UNKNOWN_SLOTS(1, 0);
};

struct PegTitle_VFTable_PegTextThing : PegTextThing_VFTable {};

static_assert(sizeof(PegTitle_VFTable) == 0x18c,
              "PegTitle_VFTable has wrong size");

struct PegTitle_Thin : PegThing_Thin, PegTextThing_Thin {
  void *mpSysButton;
  void *mpCloseButton;
  void *mpMinButton;
  void *mpMaxButton;
  void *mpMenu;
  short miHeight;
};

static_assert(sizeof(PegTitle_Thin) == 0x7c, "PegTitle_Thin has wrong size");

class PegTitle : public PegThing, public PegTextThing {
public:
  PegTitle(const PEGCHAR *title,
           WORD style = TF_SYSBUTTON | TF_MINMAXBUTTON | TF_CLOSEBUTTON);

  inline PegTitle_Thin *obj() {
    return static_cast<PegTitle_Thin *>(PegThing::_obj);
  }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegTitle(PegTitle_Thin *obj, size_t vftSize);

private:
  inline PegTitle_VFTable *vftNew() {
    return static_cast<PegTitle_VFTable *>(PegThing::_vftNew);
  }
  inline PegTitle_VFTable *vftOld() {
    return static_cast<PegTitle_VFTable *>(PegThing::_vftOld);
  }
};

extern "C" PegTitle_Thin *PegTitle_ctor(PegTitle_Thin *, const PEGCHAR *, WORD);
