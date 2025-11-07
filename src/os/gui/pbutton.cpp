#include "pbutton.hpp"
#include <cstddef>

PegButton::PegButton(PegButton_Thin *obj, size_t vftSize)
    : PegThing(obj, vftSize) {}

PegButton::PegButton(const PegRect &rect, WORD id, WORD flags)
    : PegButton(PegButton_ctor_0(0, &rect, id, flags),
                sizeof(PegButton_VFTable)) {}

PegButton::PegButton(WORD id, WORD flags)
    : PegButton(PegButton_ctor_1(0, id, flags), sizeof(PegThing_VFTable)) {}

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
