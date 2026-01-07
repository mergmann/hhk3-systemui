#pragma once

#include "ptextbox.hpp"

struct PegEditBox_VFTable : PegTextBox_VFTable {
  // PegEditBox does not appear to add new virtual slots to the primary VTable
  // (inherited from PegWindow -> PegTextBox), but it overrides existing ones.
};

// Size check: Matches PegTextBox_VFTable
static_assert(sizeof(PegEditBox_VFTable) == 0x234,
              "PegEditBox_VFTable has wrong size");

struct PegEditBox_Thin : PegTextBox_Thin {
  PegPoint mCursor;     // row, col of cursor
  PegPoint mMarkAnchor; // row, col char position of mark anchor
  PegPoint mMarkEnd;    // row, col char position of mark end
  PegPoint mCursorPos;  // top, left pixel position of cursor
  PegPoint mCursorPrev; // row, col of previous cursor
  PegPoint mCursorPosPrev;

  struct {
    SIGNED mbEditMode : 1;
    SIGNED mbMarked : 1;
    SIGNED mbMarkMode : 1;
    SIGNED bPointerSet : 1;
  } State;
};

// Size check: PegTextBox_Thin (0xAC) + 6*4 (24) + 4 = 0xC8
static_assert(sizeof(PegEditBox_Thin) == 0xC8,
              "PegEditBox_Thin has wrong size");

class PegEditBox : public PegTextBox {
public:
  PegEditBox(const PegRect &Rect, WORD wId = 0,
             WORD wStyle = FF_RECESSED | EF_EDIT | EF_WRAP,
             const PEGCHAR *Text = NULL, WORD wMaxChars = 1000);

  /**
   * @brief Get the underlying ClassPad object
   * @return ClassPad object
   */
  inline PegEditBox_Thin *obj() {
    return static_cast<PegEditBox_Thin *>(PegWindow::_obj);
  }

  // --- Non-Virtual Methods ---
  void DeleteMarkedText(void);
  void CopyToScratchPad(void);
  void PasteFromScratchPad(void);
  void HomeCursor(void);
  void InsertCharAtCursor(WORD iKey);
  void SetCursorRowColFromIndex(WORD wIndex);

  BOOL InEditMode(void) { return obj()->State.mbEditMode; }

  void MoveCursor(SIGNED delta);
  void SelectAll();
  void DrawCursor(void);
  void RemoveCursor(void);
  PEGCHAR *GetCharAtCursor(void);

protected:
  PegEditBox(PegEditBox_Thin *obj, size_t vftSize);

  // Protected non-virtuals (exposed via wrapper if needed)
  void SetEditModeState(BOOL bState);

private:
  inline PegEditBox_VFTable *vftNew() {
    return static_cast<PegEditBox_VFTable *>(PegWindow::_vftNew);
  }
  inline PegEditBox_VFTable *vftOld() {
    return static_cast<PegEditBox_VFTable *>(PegWindow::_vftOld);
  }
};
