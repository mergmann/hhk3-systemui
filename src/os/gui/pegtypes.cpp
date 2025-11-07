#include "pegtypes.hpp"

void PegRect::CenterIfLandscape(BOOL shiftUp) {
  PegRect_CenterIfLandscape(this, shiftUp);
}

void PegRect::SetAndCenterIfLandscape(SIGNED x1, SIGNED y1, SIGNED x2,
                                      SIGNED y2, BOOL shiftUp) {
  PegRect_SetAndCenterIfLandscape(this, x1, y1, x2, y2, shiftUp);
}
