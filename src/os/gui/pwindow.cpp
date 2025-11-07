#include "pwindow.hpp"
#include "util.hpp"

PegWindow::PegWindow(PegWindow_Thin *obj, size_t vftSize)
    : PegThing(obj, vftSize) {
  auto vft = vftNew();

  VFT_REGISTER(PegWindow, ExecuteFlush, (bool flush, bool destroy),
               (flush, destroy));
  VFT_REGISTER(PegWindow, Execute, (), ());
  VFT_REGISTER(PegWindow, SetScrollMode, (UCHAR mode), (mode));
  VFT_REGISTER(PegWindow, GetScrollMode, (), ());
  VFT_REGISTER(PegWindow, GetVScrollInfo, (void *info), (info));
  VFT_REGISTER(PegWindow, GetHScrollInfo, (void *info), (info));
  VFT_REGISTER(PegWindow, DrawFrame, (BOOL fill), (fill));
  VFT_REGISTER(PegWindow, MoveFocusToFirstClientChild, (), ());
  VFT_REGISTER(PegWindow, ExecuteDispatch, (PegMessage & message), (message));
  // vft->BorderContains.func = [](void *self, DUMMY, DUMMY, DUMMY,
  //                               PegPoint point) {
  //   return VFT_DISPATCH(PegWindow, BorderContains(point));
  // };

  vft->owner = this;
}

PegWindow::PegWindow(PegRect &rect, WORD style)
    : PegWindow(PegWindow_ctor_0(0, &rect, style), sizeof(PegWindow_VFTable)) {}

PegWindow::PegWindow(WORD style)
    : PegWindow(PegWindow_ctor_1(0, style), sizeof(PegWindow_VFTable)) {}

VFT_VIRTUAL(PegWindow, ExecuteFlush, SIGNED, (bool bFlush, bool bDestroy),
            (bFlush, bDestroy))
VFT_VIRTUAL(PegWindow, Execute, SIGNED, (), ())
VFT_VIRTUAL(PegWindow, SetScrollMode, void, (UCHAR uMode), (uMode))
VFT_VIRTUAL(PegWindow, GetScrollMode, UCHAR, (), ())
VFT_VIRTUAL(PegWindow, GetVScrollInfo, void, (void *put), (put))
VFT_VIRTUAL(PegWindow, GetHScrollInfo, void, (void *put), (put))
VFT_VIRTUAL(PegWindow, DrawFrame, void, (BOOL bFill), (bFill))
VFT_VIRTUAL(PegWindow, MoveFocusToFirstClientChild, void, (), ())
VFT_VIRTUAL(PegWindow, ExecuteDispatch, SIGNED, (PegMessage & message),
            (message))
// UCHAR PegWindow::BorderContains(PegPoint point) {
//   return vftOld()->BorderContains(obj(), 0, 0, 0, point);
// }
