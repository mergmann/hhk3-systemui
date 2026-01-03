#include "plist.hpp"
#include "pthing.hpp"

PegList::PegList(PegList_Thin *obj, size_t vftSize) : PegWindow(obj, vftSize) {
  auto vft = vftNew();

  VFT_REGISTER(PegList, Add, (PegThing_Thin * pWhat, BOOL bDraw),
               (pWhat, bDraw));
  VFT_REGISTER(PegList, AddToEnd, (PegThing_Thin * pWhat, BOOL bDraw),
               (pWhat, bDraw));
  VFT_REGISTER(PegList, Remove, (PegThing_Thin * pWhat, BOOL bDraw),
               (pWhat, bDraw));

  VFT_REGISTER(PegList, GetSelected, (), ());

  // Register overloaded SetSelected to specific VTable slots
  VFT_REGISTER_TO(PegList, SetSelected, SetSelectedThing, (PegThing_Thin * Who),
                  (Who));
  VFT_REGISTER_TO(PegList, SetSelected, SetSelectedIndex, (SIGNED iIndex),
                  (iIndex));

  VFT_REGISTER(PegList, GetIndex, (PegThing_Thin * Who), (Who));
  VFT_REGISTER(PegList, GetSelectedIndex, (), ());
  VFT_REGISTER(PegList, Clear, (), ());
  VFT_REGISTER(PegList, PositionChildren, (), ());

  vft->owner = this;
}

PegList::PegList(const PegRect &Rect, WORD wId, WORD wStyle)
    : PegList(PegList_ctor(0, &Rect, wId, wStyle), sizeof(PegList_VFTable)) {}

PegThing_Thin *PegList::GetSelected(void) {
  PegThing_Thin *ptr = vftOld()->GetSelected(obj());
  return ptr;
}

// Implementation for the overloaded SetSelected(PegThing*)
void PegList::SetSelected(PegThing_Thin *Who) {
  vftOld()->SetSelectedThing(obj(), Who);
}

PegThing_Thin *PegList::SetSelected(SIGNED iIndex) {
  return vftOld()->SetSelectedIndex(obj(), iIndex);
}

VFT_VIRTUAL(PegList, GetIndex, SIGNED, (PegThing_Thin * Who), (Who))
VFT_VIRTUAL(PegList, GetSelectedIndex, SIGNED, (), ())
VFT_VIRTUAL(PegList, Clear, SIGNED, (), ())
VFT_VIRTUAL(PegList, PositionChildren, void, (), ())

// Proxy Implementations

PegThing_Thin *PegList::SelectNext(void) {
  PegThing_Thin *res = PegList_SelectNext(obj());
  return res;
}

PegThing_Thin *PegList::SelectPrevious(void) {
  // TODO: this seems to be missing from ROM!!
  // PegThing_Thin *res = PegList_SelectPrevious(obj());
  // return res ? new PegThing(res) : NULL;

  PegThing_Thin *lastSelected = obj()->mpLastSelected;
  if (!lastSelected)
    return NULL;

  PegThing_Thin *prev = lastSelected->mpPrev;
  while (prev) {
    if ((prev->mwStatus & PSF_SELECTABLE) != 0) {
      SetSelected(prev);
      return GetSelected();
    }
    prev = prev->mpPrev;
  }

  // Check for Wrap (LS_WRAP_SELECT = 0x2000)
  if ((Style() & LS_WRAP_SELECT) && obj()->mpNext) {
    // Find last item
    prev = obj()->mpNext;
    while (prev->mpNext)
      prev = prev->mpNext;

    while (prev) {
      if ((prev->mwStatus & PSF_SELECTABLE) != 0) {
        if (prev == lastSelected)
          break;
        SetSelected(prev);
        return GetSelected();
      }
      prev = prev->mpPrev;
    }
  }
  return NULL;
}

PegThing_Thin *PegList::PageDown(void) { return PegList_PageDown(obj()); }

PegThing_Thin *PegList::PageUp(void) { return PegList_PageUp(obj()); }

// PegVertList and PegHorzList proxy implementations
void PegVertList::PositionChildren(void) {
  PegVertList_PositionChildren(obj());
}

void PegHorzList::PositionChildren(void) {
  PegHorzList_PositionChildren(obj());
}