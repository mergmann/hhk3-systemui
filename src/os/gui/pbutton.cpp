#include "pbutton.hpp"
#include "pegtypes.hpp"
#include "util.hpp"
#include <cstddef>

extern "C" {
PegButton_Thin *PegButton_ctor_0(PegButton_Thin *, const PegRect *, WORD, WORD);
PegButton_Thin *PegButton_ctor_1(PegButton_Thin *, WORD, WORD);

PegTextButton_Thin *PegTextButton_ctor_0(PegTextButton_Thin *, PegRect *,
                                         const PEGCHAR *, WORD, WORD, COLORVAL);
PegTextButton_Thin *PegTextButton_ctor_1(PegTextButton_Thin *, SIGNED, SIGNED,
                                         SIGNED, const PEGCHAR *, WORD, WORD,
                                         COLORVAL);
PegTextButton_Thin *PegTextButton_ctor_2(PegTextButton_Thin *, SIGNED, SIGNED,
                                         const PEGCHAR *, WORD, WORD, COLORVAL);

PegRadioButton_Thin *PegRadioButton_ctor_0(PegRadioButton *, SIGNED, SIGNED,
                                           const PEGCHAR *, WORD, WORD,
                                           PegFont *, BOOL);
PegRadioButton_Thin *PegRadioButton_ctor_1(PegRadioButton *, PegRect *,
                                           const PEGCHAR *, WORD, WORD);
}

// **************** //
// *    Button    * //
// **************** //

PegButton::PegButton(PegButton_Thin *obj, size_t vftSize)
    : PegThing(obj, vftSize) {}

PegButton::PegButton(const PegRect &rect, WORD id, WORD flags)
    : PegButton(PegButton_ctor_0(0, &rect, id, flags),
                sizeof(PegButton_VFTable)) {}

PegButton::PegButton(WORD id, WORD flags)
    : PegButton(PegButton_ctor_1(0, id, flags), sizeof(PegThing_VFTable)) {}

// **************** //
// * Text Button  * //
// **************** //

PegTextButton::PegTextButton(PegTextButton_Thin *inner, size_t vftSize)
    : PegButton(inner, vftSize),
      PegTextThing(inner, sizeof(PegTextThing_VFTable)) {}

PegTextButton::PegTextButton(PegRect &rect, const PEGCHAR *text, WORD id,
                             WORD style, COLORVAL color)
    : PegTextButton(PegTextButton_ctor_0(0, &rect, text, id, style, color),
                    sizeof(PegTextButton_VFTable)) {}

PegTextButton::PegTextButton(SIGNED x, SIGNED y, SIGNED w, const PEGCHAR *text,
                             WORD id, WORD style, COLORVAL color)
    : PegTextButton(PegTextButton_ctor_1(0, x, y, w, text, id, style, color),
                    sizeof(PegTextButton_VFTable)) {}

PegTextButton::PegTextButton(SIGNED x, SIGNED y, const PEGCHAR *text, WORD id,
                             WORD style, COLORVAL color)
    : PegTextButton(PegTextButton_ctor_2(0, x, y, text, id, style, color),
                    sizeof(PegTextButton_VFTable)) {}

// **************** //
// * Radio Button * //
// **************** //

PegRadioButton::PegRadioButton(PegRadioButton_Thin *inner, size_t vftSize)
    : PegButton(inner, vftSize),
      PegTextThing(inner, sizeof(PegTextThing_VFTable)) {
  VFT_REGISTER(PegRadioButton, SetSelected, (BOOL select), (select));
  VFT_REGISTER(PegRadioButton, IsSelected, (), ());
}

PegRadioButton::PegRadioButton(SIGNED x, SIGNED y, const PEGCHAR *text, WORD id,
                               WORD style, PegFont *font, BOOL unknown)
    : PegRadioButton(
          PegRadioButton_ctor_0(0, x, y, text, id, style, font, unknown),
          sizeof(PegRadioButton_VFTable)) {}

PegRadioButton::PegRadioButton(PegRect &rect, const PEGCHAR *text, WORD id,
                               WORD style)
    : PegRadioButton(PegRadioButton_ctor_1(0, &rect, text, id, style),
                     sizeof(PegRadioButton_VFTable)) {}

VFT_VIRTUAL(PegRadioButton, SetSelected, void, (BOOL select), (select))
VFT_VIRTUAL(PegRadioButton, IsSelected, BOOL, (), ())
