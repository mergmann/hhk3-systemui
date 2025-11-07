#include "ptitle.hpp"
#include "pfonts.hpp"
#include <cstddef>

PegTitle::PegTitle(PegTitle_Thin *obj, size_t vftSize)
    : PegThing(obj, vftSize), PegTextThing(obj, sizeof(PegTextThing_VFTable)) {}

PegTitle::PegTitle(const PEGCHAR *title, WORD style)
    : PegTitle(PegTitle_ctor(0, title, style), sizeof(PegTitle_VFTable)) {}
