#include "peditbox.hpp"
#include "pegtypes.hpp"
#include "util.hpp"

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

// --- Virtual Overrides Implementations ---

VFT_VIRTUAL(PegEditBox, Draw, void, (), ());
// VFT_VIRTUAL(PegEditBox, Message, SIGNED, (const PegMessage &Mesg), (Mesg));
VFT_VIRTUAL(PegEditBox, DataSet, void, (const PEGCHAR *pText), (pText));
VFT_VIRTUAL(PegEditBox, Append, void, (const PEGCHAR *pText, BOOL bDraw),
            (pText, bDraw));
VFT_VIRTUAL(PegEditBox, Resize, void, (PegRect NewSize), (NewSize));

// --- Non-Virtual Proxy Implementations ---

void PegEditBox::DeleteMarkedText(void) {
  PegEditBox_DeleteMarkedText(obj());
}

void PegEditBox::CopyToScratchPad(void) {
  PegEditBox_CopyToScratchPad(obj());
}

void PegEditBox::PasteFromScratchPad(void) {
  PegEditBox_PasteFromScratchPad(obj());
}

void PegEditBox::HomeCursor(void) {
  PegEditBox_HomeCursor(obj());
}

void PegEditBox::InsertCharAtCursor(WORD iKey) {
  PegEditBox_InsertCharAtCursor(obj(), iKey);
}

void PegEditBox::SetCursorRowColFromIndex(WORD wIndex) {
  PegEditBox_SetCursorRowColFromIndex(obj(), wIndex);
}

void PegEditBox::MoveCursor(SIGNED delta) {
  PegEditBox_MoveCursor(obj(), delta);
}

void PegEditBox::SelectAll() {
  PegEditBox_SelectAll(obj());
}

void PegEditBox::DrawCursor(void) {
  PegEditBox_DrawCursor(obj());
}

void PegEditBox::RemoveCursor(void) {
  PegEditBox_RemoveCursor(obj());
}

PEGCHAR *PegEditBox::GetCharAtCursor(void) {
  return PegEditBox_GetCharAtCursor(obj());
}

void PegEditBox::SetEditModeState(BOOL bState) {
  PegEditBox_SetEditModeState(obj(), bState);
}