#pragma once

#include "pegtypes.hpp"
#include "pthing.hpp"
#include "util.hpp"
#include <cstdint>

class PegScreen_Thin;

extern "C" void PegScreen_Invalidate(PegScreen_Thin *, const PegRect *);

struct PegScreen_VFTable : Element_VFTable {
  VFTableFunction<void, bool> _dtor;
  VFTableFunction<void, SIGNED, SIGNED, SIGNED, COLORVAL, UCHAR> PlotPointView;
  VFTableFunction<void, SIGNED, SIGNED, SIGNED, COLORVAL, UCHAR>
      PlotRopPointView;
  VFTableFunction<void, PegThing_Thin *> BeginDraw_0;
  VFTableFunction<void, PegThing_Thin *, PegBitmap *> BeginDraw_1;
  VFTableFunction<void> EndDraw_0;
  VFTableFunction<void, PegBitmap *> EndDraw_1;
  VFTableFunction<void, void *, PegRect *> Capture;
  VFTableFunction<void, SIGNED, SIGNED, UCHAR *> SetPalette;
  VFTableFunction<void> ResetPalette;
  VFTableFunction<COLORVAL, PegThing_Thin *, SIGNED, SIGNED> GetPixel;
  VFTableFunction<void, PegThing_Thin *, SIGNED, SIGNED, COLORVAL, UCHAR>
      PutPixel;
  VFTableFunction<DWORD> NumColors;
  VFTableFunction<PegBitmap *, SIGNED, SIGNED> CreateBitmap;
  VFTableFunction<void, PegBitmap *> DestroyBitmap;
  VFTableFunction<void, PegThing *, SIGNED, SIGNED, SIGNED, SIGNED,
                  const PegColor *, SIGNED, UCHAR>
      Line;
  VFTableFunction<void, PegThing *, const PegRect *, const PegColor *, SIGNED,
                  UCHAR, SIGNED>
      Rectangle_0;
  VFTableFunction<void, const PegRect *, PegRect *, const PegColor *, SIGNED,
                  UCHAR, SIGNED>
      Rectangle_1;
  VFT_UNKNOWN_SLOTS(6, 0);
  VFTableFunction<void, PegThing *, PegBitmap *, BOOL, PegPoint, UCHAR> Bitmap;
  VFTableFunction<void, PegThing *, PegRect, PegBitmap *> BitmapFill;

  // Too lazy, someone else continue
  VFT_UNKNOWN_SLOTS(30, 1);
};

static_assert(sizeof(PegScreen_VFTable) == 0x2ac,
              "PegScreen_VFTable has wrong size");

class PegScreen_Thin : Element_Thin {
public:
  inline void Invalidate(const PegRect &area) {
    PegScreen_Invalidate(this, &area);
  }

protected:
  void *mpFreeListStart;
  void *mpFreeListEnd;
  void *mpAllocatedBlocks;
  PegRect mInvalid;
  PegRect mVirtualRect;
  SIGNED mwHRes;
  SIGNED mwVRes;
  DWORD mdNumColors;
  WORD mwTotalViewports;
  WORD mwDrawNesting;
  SIGNED miInvalidCount;
  BOOL mbVirtualDraw;
  COLORVAL **mpScanPointers;
  COLORVAL **mpSaveScanPointers;

private:
  [[maybe_unused]] uint32_t unk00;
  [[maybe_unused]] uint32_t unk01;
  [[maybe_unused]] uint32_t unk02;
  [[maybe_unused]] uint32_t unk03;
  PegRect mScreenRect;

  [[maybe_unused]] uint32_t unk04;

  void *_vft;

  inline PegThing_VFTable *vft() {
    return static_cast<PegThing_VFTable *>(_vft);
  }
};

static_assert(sizeof(PegScreen_Thin) == 0x58, "PegScreen_Thin has wrong size");