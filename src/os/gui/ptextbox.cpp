#include "ptextbox.hpp"
#include "pegtypes.hpp"
#include "pfonts.hpp"
#include "util.hpp"

PegTextBox::PegTextBox(PegTextBox_Thin *obj, size_t vftSize)
    : PegWindow(obj, vftSize), PegTextThing(obj, sizeof(PegTextThing_VFTable)) {
  VFT_REGISTER(PegTextBox, DataSet, (const PEGCHAR *text), (text));
  VFT_REGISTER(PegTextBox, Append, (const PEGCHAR *text, BOOL draw),
               (text, draw));
  VFT_REGISTER(PegTextBox, SetFont, (PegFont * font), (font));
  vftNew()->DrawTextLine.func = [](void *self, SIGNED line, BOOL fill, DUMMY,
                                   PegPoint point) {
    static_cast<PegTextBox *>(
        static_cast<PegTextBox_Thin *>(self)->vft()->owner)
        ->DrawTextLine(line, point, fill);
  };
}

PegTextBox::PegTextBox(PegRect &rect, WORD id, WORD style, const PEGCHAR *text,
                       WORD maxChars)
    : PegTextBox(PegTextBox_ctor(0, &rect, id, style, text, maxChars),
                 sizeof(PegTextBox_VFTable)) {}

VFT_VIRTUAL(PegTextBox, Append, void, (const PEGCHAR *text, BOOL draw),
            (text, draw))

void PegTextBox::DrawTextLine(SIGNED line, PegPoint point, BOOL fill) {
  vftOld()->DrawTextLine(obj(), line, fill, 0, point);
}
