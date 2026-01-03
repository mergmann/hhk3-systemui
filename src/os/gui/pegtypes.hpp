#pragma once

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned short WORD;
typedef long LONG;
typedef unsigned long DWORD;
typedef short int SIGNED;
typedef char PEGCHAR;
typedef WORD COLORVAL;

const WORD FF_NONE = 0x0001;
const WORD FF_THIN = 0x0002;
const WORD FF_THICK = 0x0010;
const WORD FF_MASK = 0x001f;
const WORD FF_RAISED = FF_THIN;
const WORD FF_RECESSED = FF_THIN;

const WORD TF_NONE = 0x0000;
const WORD TF_SYSBUTTON = 0x0200;
const WORD TF_MINMAXBUTTON = 0x0400;
const WORD TF_CLOSEBUTTON = 0x0800;

const WORD EF_EDIT = 0x0100;
const WORD EF_PARTIALROW = 0x0200;
const WORD EF_WRAP = 0x0400;
const WORD EF_FULL_SELECT = 0x0800;
const WORD EF_CHARWRAP = 0x1000;

const WORD MW_OK = 0x0020;
const WORD MW_YES = 0x0040;
const WORD MW_NO = 0x0080;
const WORD MW_ABORT = 0x0100;
const WORD MW_RETRY = 0x0200;
const WORD MW_CANCEL = 0x0400;
const WORD MW_SET = 0x0001;
const WORD MW_INPUT = 0x0002;
const WORD MW_COPY = 0x0004;
const WORD MW_EXE = 0x0008;
const WORD MW_GOTO = 0x0010;
const WORD MW_ESC = 0x0020;

const WORD AF_TRANSPARENT = 0x4000;
const WORD AF_ENABLED = 0x8000;

const WORD TJ_RIGHT = 0x0020;
const WORD TJ_LEFT = 0x0040;
const WORD TJ_CENTER = 0x0080;
const WORD TJ_MASK = 0x00E0;


#define PEG_FIRST_SIGNAL 0x80
#define PEG_FIRST_USER_MESSAGE 0x4000
#define PEG_SIGNAL(id, signal) (PEG_FIRST_SIGNAL + ((id) << 4) + signal)

struct PegRect;

extern "C" void PegRect_CenterIfLandscape(PegRect *self, BOOL shiftUp);
extern "C" void PegRect_SetAndCenterIfLandscape(PegRect *self, SIGNED x1,
                                                SIGNED y1, SIGNED x2, SIGNED y2,
                                                BOOL shiftUp);

const UCHAR CF_NONE = 0x00;
const UCHAR CF_FILL = 0x01;
const UCHAR CF_DASHED = 0x02;
const UCHAR CF_XOR = 0x04;
const UCHAR CF_ALPHA = 0x08;

struct PegColor {
  PegColor(COLORVAL fg, COLORVAL bg = 0xFFFF, UCHAR flags = CF_NONE) {
    uForeground = fg;
    uBackground = bg;
    uFlags = flags;
  }

  PegColor() {
    uForeground = uBackground = 0x0000;
    uFlags = CF_NONE;
  }

  void Set(COLORVAL fg, COLORVAL bg = 0x0000, UCHAR flags = CF_NONE) {
    uForeground = fg;
    uBackground = bg;
    uFlags = flags;
  }

  COLORVAL uForeground;
  COLORVAL uBackground;
  UCHAR uFlags;
};

/*--------------------------------------------------------------------------*/
// System Status flags common to all object types
// These flags are maintained internally by PEG, but can be modified (at your
// own risk!) by the application level software.
/*--------------------------------------------------------------------------*/

const WORD PSF_VISIBLE =           0x0001;
const WORD PSF_CURRENT =           0x0002;
const WORD PSF_SELECTABLE =        0x0004;
const WORD PSF_SIZEABLE =          0x0008;
const WORD PSF_MOVEABLE =          0x0010;
const WORD PSF_NONCLIENT =         0x0020;
const WORD PSF_ACCEPTS_FOCUS =     0x0040;
const WORD PSF_KEEPS_CHILD_FOCUS = 0x0080;
const WORD PSF_CONTINUOUS_SCROLL = 0x0100;
const WORD PSF_TAB_STOP =          0x0200;
const WORD PSF_OWNS_POINTER =      0x0400;    
const WORD PSF_ALWAYS_ON_TOP =     0x4000;
const WORD PSF_VIEWPORT =          0x8000;

/// @name List Style
const WORD LS_WRAP_SELECT = 0x2000;	///< @hideinitializer wrap select

struct PegPoint {
  BOOL operator!=(const PegPoint &other) const {
    if (x != other.x || y != other.y) {
      return TRUE;
    }
    return FALSE;
  }

  BOOL operator==(const PegPoint &other) const {
    if (x == other.x && y == other.y) {
      return TRUE;
    }
    return FALSE;
  }

  PegPoint operator+(const PegPoint &other) const {
    PegPoint out;
    out.x = x + other.x;
    out.y = y + other.y;
    return out;
  }

  SIGNED x;
  SIGNED y;
};

struct PegRect {
  inline PegRect() {}

  inline PegRect(SIGNED x1, SIGNED y1, SIGNED x2, SIGNED y2) {
    wLeft = x1;
    wTop = y1;
    wRight = x2;
    wBottom = y2;
  }

  inline void Set(SIGNED x1, SIGNED y1, SIGNED x2, SIGNED y2) {
    wLeft = x1;
    wTop = y1;
    wRight = x2;
    wBottom = y2;
  }

  inline void CenterIfLandscape(BOOL shiftUp) {
    PegRect_CenterIfLandscape(this, shiftUp);
  }

  inline void SetAndCenterIfLandscape(SIGNED x1, SIGNED y1, SIGNED x2,
                                      SIGNED y2, BOOL shiftUp) {
    PegRect_SetAndCenterIfLandscape(this, x1, y1, x2, y2, shiftUp);
  }

  SIGNED wLeft;
  SIGNED wTop;
  SIGNED wRight;
  SIGNED wBottom;
};

struct PegBitmap {
  UCHAR uFlags;
  UCHAR uBitsPix;
  WORD wWidth;
  WORD wHeight;
  DWORD dTransColor;
  UCHAR *pStart;
};