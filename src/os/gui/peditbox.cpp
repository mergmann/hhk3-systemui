#include "peditbox.hpp"
#include "pegtypes.hpp"
#include "util.hpp"

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

PegEditBox::PegEditBox(PegEditBox_Thin *obj, size_t vftSize)
    : PegTextBox(obj, vftSize) {
  // Register overrides
  VFT_REGISTER(PegEditBox, Draw, (), ());
  // VFT_REGISTER(PegEditBox, Message, (const PegMessage &Mesg), (Mesg));
  VFT_REGISTER(PegEditBox, DataSet, (const PEGCHAR *pText), (pText));
  VFT_REGISTER(PegEditBox, Append, (const PEGCHAR *pText, BOOL bDraw),
               (pText, bDraw));
  VFT_REGISTER(PegEditBox, Resize, (PegRect NewSize), (NewSize));
}

PegEditBox::PegEditBox(const PegRect &Rect, WORD wId, WORD wStyle,
                       const PEGCHAR *Text, WORD wMaxChars)
    : PegEditBox(PegEditBox_ctor(0, &Rect, wId, wStyle, Text, wMaxChars),
                 sizeof(PegEditBox_VFTable)) {}

// --- Non-Virtual Proxy Implementations ---

void PegEditBox::DeleteMarkedText(void) { PegEditBox_DeleteMarkedText(obj()); }

void PegEditBox::CopyToScratchPad(void) { PegEditBox_CopyToScratchPad(obj()); }

void PegEditBox::PasteFromScratchPad(void) {
  PegEditBox_PasteFromScratchPad(obj());
}

void PegEditBox::HomeCursor(void) { PegEditBox_HomeCursor(obj()); }

void PegEditBox::InsertCharAtCursor(WORD iKey) {
  PegEditBox_InsertCharAtCursor(obj(), iKey);
}

void PegEditBox::SetCursorRowColFromIndex(WORD wIndex) {
  PegEditBox_SetCursorRowColFromIndex(obj(), wIndex);
}

void PegEditBox::MoveCursor(SIGNED delta) {
  PegEditBox_MoveCursor(obj(), delta);
}

void PegEditBox::SelectAll() { PegEditBox_SelectAll(obj()); }

void PegEditBox::DrawCursor(void) { PegEditBox_DrawCursor(obj()); }

void PegEditBox::RemoveCursor(void) { PegEditBox_RemoveCursor(obj()); }

PEGCHAR *PegEditBox::GetCharAtCursor(void) {
  return PegEditBox_GetCharAtCursor(obj());
}

void PegEditBox::SetEditModeState(BOOL bState) {
  PegEditBox_SetEditModeState(obj(), bState);
}