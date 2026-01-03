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
  PegPoint mCursor;       // row, col of cursor
  PegPoint mMarkAnchor;   // row, col char position of mark anchor
  PegPoint mMarkEnd;      // row, col char position of mark end
  PegPoint mCursorPos;    // top, left pixel position of cursor
  PegPoint mCursorPrev;   // row, col of previous cursor
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

  // --- Virtual Overrides ---
  virtual void Draw(void);
  virtual SIGNED Message(const PegMessage &Mesg);
  virtual void DataSet(const PEGCHAR *pText);
  virtual void Append(const PEGCHAR *pText, BOOL bDraw = TRUE);
  virtual void Resize(PegRect NewSize);

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

// C Exports
extern "C" {
	// Constructor (inferred from dump reference 8025fd7a)
	PegEditBox_Thin *PegEditBox_ctor(PegEditBox_Thin *, const PegRect *, WORD, WORD,
																	const PEGCHAR *, WORD);

	// Non-virtual placeholders
	void PegEditBox_DeleteMarkedText(PegEditBox_Thin *);
	void PegEditBox_CopyToScratchPad(PegEditBox_Thin *);
	void PegEditBox_PasteFromScratchPad(PegEditBox_Thin *);
	void PegEditBox_HomeCursor(PegEditBox_Thin *);
	void PegEditBox_InsertCharAtCursor(PegEditBox_Thin *, WORD);
	void PegEditBox_SetCursorRowColFromIndex(PegEditBox_Thin *, WORD);
	void PegEditBox_MoveCursor(PegEditBox_Thin *, SIGNED);
	void PegEditBox_SelectAll(PegEditBox_Thin *);
	void PegEditBox_DrawCursor(PegEditBox_Thin *);
	void PegEditBox_RemoveCursor(PegEditBox_Thin *);
	PEGCHAR *PegEditBox_GetCharAtCursor(PegEditBox_Thin *);
	void PegEditBox_SetEditModeState(PegEditBox_Thin *, BOOL);
}