#pragma once

#include "pdecwin.hpp"
#include <cstdint>

struct PegDialog_VFTable : PegDecoratedWindow_VFTable {};

static_assert(sizeof(PegDialog_VFTable) == 0x204,
              "PegDecoratedWindow_VFTable has wrong size");

struct PegDialog_Thin : PegDecoratedWindow_Thin {
protected:
  PegThing *mpReportTo;
  uint32_t unknown[3];
  PegThing *pLastFocus;
};

static_assert(sizeof(PegDialog_Thin) == 0x90, "PegDialog_Thin has wrong size");
