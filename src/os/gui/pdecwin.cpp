#include "pdecwin.hpp"

PegDecoratedWindow::PegDecoratedWindow(PegDecoratedWindow_Thin *obj,
                                       size_t vftSize)
    : PegWindow(obj, vftSize) {}

PegDecoratedWindow::PegDecoratedWindow(PegRect &rect, WORD style)
    : PegDecoratedWindow(PegDecoratedWindow_ctor_0(0, &rect, style),
                         sizeof(PegDecoratedWindow_VFTable)) {}
PegDecoratedWindow::PegDecoratedWindow(WORD style)
    : PegDecoratedWindow(PegDecoratedWindow_ctor_1(0, style),
                         sizeof(PegDecoratedWindow_VFTable)) {}
