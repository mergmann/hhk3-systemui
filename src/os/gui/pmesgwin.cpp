#include "pmesgwin.hpp"
#include "pegtypes.hpp"
#include "pfonts.hpp"
#include "pwindow.hpp"
#include "util.hpp"
#include <cstddef>

PegMessageWindow::PegMessageWindow(PegMessageWindow_Thin *obj, size_t vftSize)
    : PegWindow(obj, vftSize), PegTextThing(obj, sizeof(PegTextThing_VFTable)) {
}

PegMessageWindow::PegMessageWindow(const PEGCHAR *title, const PEGCHAR *message,
                                   WORD style, WORD style2, void *icon,
                                   PegThing *owner)
    : PegWindow(PegMessageWindow_ctor_0(0, title, message, style, style2, icon,
                                        owner),
                sizeof(PegMessageWindow_VFTable)) {}

PegMessageWindow::PegMessageWindow(const PEGCHAR *title, const PEGCHAR *message,
                                   const PEGCHAR *comment, WORD style,
                                   WORD style2, void *icon, WORD unknown,
                                   MessageWindowTypeEnum type)
    : PegWindow(PegMessageWindow_ctor_1(0, title, message, comment, style,
                                        style2, icon, unknown, type),
                sizeof(PegMessageWindow_VFTable)) {}

VFT_VIRTUAL_TO(PegMessageWindow, Style2, Style2_0, WORD, (), ())
VFT_VIRTUAL_TO(PegMessageWindow, Style2, Style2_1, void, (WORD style2),
               (style2))
