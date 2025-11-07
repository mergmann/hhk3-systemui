#include "pthing.hpp"
#include "pmessage.hpp"
#include "util.hpp"
#include <sdk/os/mem.h>

PegThing::PegThing(PegThing_Thin *obj, size_t vftSize) : Element(obj) {
  _vftOld = obj->_vft;
  _vftNew = Mem_Malloc(vftSize);

  Mem_Memcpy(_vftNew, obj->_vft, vftSize);
  obj->_vft = vftNew();

  auto vft = vftNew();
  vft->owner = this;

  VFT_REGISTER(PegThing, Message, (const PegMessage *mesg), (*mesg));
  VFT_REGISTER(PegThing, Draw, (), ());
  VFT_REGISTER(PegThing, Add, (PegThing_Thin * what, BOOL draw), (what, draw));
  VFT_REGISTER(PegThing, AddToEnd, (PegThing_Thin * thing, BOOL draw),
               (thing, draw));
  VFT_REGISTER(PegThing, NotifyChildRemoved, (PegThing_Thin * thing), (thing));
  VFT_REGISTER(PegThing, Remove, (PegThing_Thin * thing, BOOL draw),
               (thing, draw));
  VFT_REGISTER(PegThing, Center, (PegThing_Thin * thing), (thing));
  VFT_REGISTER(PegThing, DrawChildren, (), ());
  VFT_REGISTER(PegThing, Resize, (PegRect rect), (rect));
  VFT_REGISTER(PegThing, Find, (WORD id, BOOL recursive), (id, recursive));
  VFT_REGISTER(PegThing, AddStatus, (WORD status), (status));
  VFT_REGISTER(PegThing, RemoveStatus, (WORD status), (status));
  VFT_REGISTER_TO(PegThing, Style, Style_0, (), ());
  VFT_REGISTER_TO(PegThing, Style, Style_1, (WORD style), (style));
  VFT_REGISTER(PegThing, InitClient, (), ());
  VFT_REGISTER(PegThing, SendSignal, (UCHAR signal), (signal));
  VFT_REGISTER(PegThing, ParentShift, (SIGNED x, SIGNED y), (x, y));
  VFT_REGISTER(PegThing, HasDefaultFocus, (), ());
  VFT_REGISTER(PegThing, GetDefaultFocus, (), ());
  VFT_REGISTER(PegThing, SetDefaultFocus, (PegThing_Thin * thing), (thing));
  VFT_REGISTER(PegThing, PasteStringInput,
               (PegThing_Thin * thing, const PEGCHAR *text), (thing, text));
  VFT_REGISTER(PegThing, RecordMouseMessage, (const PegMessage *mesg), (*mesg));
  VFT_REGISTER(PegThing, RecordKeyMessage, (const PegMessage *mesg), (*mesg));
  VFT_REGISTER(PegThing, RecordSystemMessage, (const PegMessage *mesg),
               (*mesg));
}

PegThing::PegThing(const PegRect &rect, WORD id, WORD style)
    : PegThing(PegThing_ctor_0(0, &rect, id, style), sizeof(PegThing_VFTable)) {
}

PegThing::PegThing(WORD id, WORD style)
    : PegThing(PegThing_ctor_1(0, id, style), sizeof(PegThing_VFTable)) {}

PegThing::~PegThing() { Mem_Free(_vftNew); }

VFT_VIRTUAL(PegThing, Message, SIGNED, (const PegMessage &mesg), (&mesg))
VFT_VIRTUAL(PegThing, Draw, void, (), ())
VFT_VIRTUAL(PegThing, Add, void, (PegThing_Thin * thing, BOOL draw),
            (thing, draw))
VFT_VIRTUAL(PegThing, AddToEnd, void, (PegThing_Thin * thing, BOOL draw),
            (thing, draw))
VFT_VIRTUAL(PegThing, NotifyChildRemoved, void, (PegThing_Thin * thing),
            (thing))
VFT_VIRTUAL(PegThing, Remove, PegThing_Thin *,
            (PegThing_Thin * thing, BOOL draw), (thing, draw))
VFT_VIRTUAL(PegThing, Center, void, (PegThing_Thin * thing), (thing))
VFT_VIRTUAL(PegThing, DrawChildren, void, (), ())
VFT_VIRTUAL(PegThing, Resize, void, (PegRect rect), (rect))
VFT_VIRTUAL(PegThing, Find, PegThing_Thin *, (WORD id, BOOL recursive),
            (id, recursive))
VFT_VIRTUAL(PegThing, AddStatus, void, (WORD status), (status))
VFT_VIRTUAL(PegThing, RemoveStatus, void, (WORD mask), (mask))

VFT_VIRTUAL_TO(PegThing, Style, Style_0, WORD, (), ())
VFT_VIRTUAL_TO(PegThing, Style, Style_1, void, (WORD style), (style))

VFT_VIRTUAL(PegThing, InitClient, void, (), ())
VFT_VIRTUAL(PegThing, SendSignal, void, (UCHAR uSignal), (uSignal))
VFT_VIRTUAL(PegThing, ParentShift, void, (SIGNED x, SIGNED y), (x, y))
VFT_VIRTUAL(PegThing, HasDefaultFocus, BOOL, (), ())
VFT_VIRTUAL(PegThing, GetDefaultFocus, PegThing_Thin *, (), ())
VFT_VIRTUAL(PegThing, SetDefaultFocus, void, (PegThing_Thin * thing), (thing))
VFT_VIRTUAL(PegThing, PasteStringInput, BOOL,
            (PegThing_Thin * thing, const PEGCHAR *str), (thing, str))
VFT_VIRTUAL(PegThing, RecordMouseMessage, void, (const PegMessage &mesg),
            (&mesg))
VFT_VIRTUAL(PegThing, RecordKeyMessage, void, (const PegMessage &mesg), (&mesg))
VFT_VIRTUAL(PegThing, RecordSystemMessage, void, (const PegMessage &mesg),
            (&mesg))
