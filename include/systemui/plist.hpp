#pragma once

#include "pegtypes.hpp"
#include "pthing.hpp" // PegThing/PegThing_Thin
#include "pwindow.hpp"
#include "util.hpp"

// Forward declare
class PegList;

struct PegList_VFTable : PegWindow_VFTable {
  VFTableFunction<PegThing_Thin *> GetSelected;
  VFTableFunction<void, PegThing_Thin *> SetSelectedThing;
  VFTableFunction<PegThing_Thin *, SIGNED> SetSelectedIndex;
  VFTableFunction<SIGNED, PegThing_Thin *> GetIndex;
  VFTableFunction<SIGNED> GetSelectedIndex;
  VFTableFunction<SIGNED> Clear;
  VFTableFunction<void> PositionChildren;
};

// Size check: PegWindow_VFTable (0x204) + 7 * 12 = 0x258
// size might need adjustment.
static_assert(sizeof(PegList_VFTable) == 0x258,
              "PegList_VFTable has wrong size");

struct PegList_Thin : PegWindow_Thin {
  PegThing_Thin *mpLastSelected;
  SIGNED miChildSeperation;
  BOOL mbNewLast;

  inline PegWindow_VFTable *vft() {
    return static_cast<PegWindow_VFTable *>(_vft);
  }
};

// Size check: PegWindow_Thin (0x6C) + 3 * 4 = 0x78
static_assert(sizeof(PegList_Thin) == 0x78, "PegList_Thin has wrong size");

class PegList : public PegWindow {
public:
  PegList(const PegRect &Rect, WORD wId = 0, WORD wStyle = FF_THIN);

  /**
   * @brief Get the underlying ClassPad object
   * @return ClassPad object
   */
  inline PegList_Thin *obj() {
    return static_cast<PegList_Thin *>(PegWindow::_obj);
  }

  /*
  virtual void Add(PegThing *pWhat, BOOL bDraw = TRUE);
  virtual void AddToEnd(PegThing *pWhat, BOOL bDraw = TRUE);
  virtual PegThing *Remove(PegThing *pWhat, BOOL bDraw = TRUE);
  */

  virtual PegThing_Thin *GetSelected(void);
  virtual void SetSelected(PegThing_Thin *Who);
  virtual SIGNED GetIndex(PegThing_Thin *Who);
  virtual SIGNED GetSelectedIndex(void);
  virtual PegThing_Thin *SetSelected(SIGNED iIndex);
  virtual SIGNED Clear();

  // Helper functions provided by the SDK logic (not in VTable)
  PegThing_Thin *SelectNext(void);
  PegThing_Thin *SelectPrevious(void);
  PegThing_Thin *PageDown(void);
  PegThing_Thin *PageUp(void);

  void SetSeperation(SIGNED iSep) { obj()->miChildSeperation = iSep; }

protected:
  PegList(PegList_Thin *obj, size_t vftSize);

  virtual void PositionChildren(void) = 0;

private:
  inline PegList_VFTable *vftNew() {
    return static_cast<PegList_VFTable *>(PegWindow::_vftNew);
  }
  inline PegList_VFTable *vftOld() {
    return static_cast<PegList_VFTable *>(PegWindow::_vftOld);
  }

  friend class PegHorzList;
  friend class PegVertList;
};

class PegVertList : public PegList {
public:
  PegVertList(const PegRect &Rect, WORD wId = 0, WORD wStyle = FF_THIN);

protected:
  virtual void PositionChildren(void);
};

class PegHorzList : public PegList {
public:
  PegHorzList(const PegRect &Rect, WORD wId = 0, WORD wStyle = FF_THIN);

protected:
  virtual void PositionChildren(void);
};
// C-style exports for OS functions
extern "C" {
PegList_Thin *PegList_ctor(PegList_Thin *, const PegRect *, WORD, WORD);

PegThing_Thin *PegList_SelectNext(PegList_Thin *self);
PegThing_Thin *PegList_SelectPrevious(PegList_Thin *self);
PegThing_Thin *PegList_PageDown(PegList_Thin *self);
PegThing_Thin *PegList_PageUp(PegList_Thin *self);

void PegVertList_PositionChildren(PegList_Thin *self);
void PegHorzList_PositionChildren(PegList_Thin *self);
}