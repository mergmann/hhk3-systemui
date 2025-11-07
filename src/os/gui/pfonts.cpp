#include "pfonts.hpp"
#include "pegtypes.hpp"
#include "util.hpp"
#include <cstdio>
#include <cstring>
#include <sdk/os/mem.h>

PegTextThing::PegTextThing(PegTextThing_Thin *obj, size_t vftSize)
    : Element(obj) {
  _vftOld = obj->_vft;
  _vftNew = Mem_Malloc(vftSize);

  Mem_Memcpy(_vftNew, obj->_vft, vftSize);
  obj->_vft = _vftNew;

  vftNew()->owner = this;

  VFT_REGISTER(PegTextThing, DataSet, (const PEGCHAR *text), (text));
  VFT_REGISTER(PegTextThing, SetFont, (PegFont * font), (font));
  VFT_REGISTER(PegTextThing, GetFont, (), ());
  VFT_REGISTER(PegTextThing, TextLength, (), ());
}

PegTextThing::PegTextThing(const PEGCHAR *text, WORD copy, UCHAR fontIndex)
    : PegTextThing(PegTextThing_ctor_0(0, text, copy, fontIndex),
                   sizeof(PegTextThing_VFTable)) {}
PegTextThing::PegTextThing(WORD copy, UCHAR fontIndex)
    : PegTextThing(PegTextThing_ctor_1(0, copy, fontIndex),
                   sizeof(PegTextThing_VFTable)) {}

PegTextThing::~PegTextThing() { Mem_Free(_vftNew); }

VFT_VIRTUAL(PegTextThing, DataSet, void, (const PEGCHAR *text), (text))
VFT_VIRTUAL(PegTextThing, SetFont, void, (PegFont * font), (font))
VFT_VIRTUAL(PegTextThing, GetFont, PegFont *, (), ())
VFT_VIRTUAL(PegTextThing, TextLength, WORD, (), ())
