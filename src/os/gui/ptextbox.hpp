#pragma once

#include "pfonts.hpp"
#include "pwindow.hpp"
#include "util.hpp"

struct PegTextBox_VFTable : PegWindow_VFTable {
  VFTableFunction<void, const PEGCHAR *> DataSet;
  VFTableFunction<void, const PEGCHAR *, BOOL> Append;
  VFTableFunction<void, PegFont *> SetFont;
  VFTableFunction<void, SIGNED, BOOL, DUMMY, PegPoint> DrawTextLine;
};

static_assert(sizeof(PegTextBox_VFTable) == 0x234,
              "PegTextBox_VFTable has wrong size");

struct PegTextBox_Thin : PegWindow_Thin, PegTextThing_Thin {
public:
  VFT_FORWARD(Append, void, (const PEGCHAR *text, BOOL draw = TRUE),
              (text, draw))

protected:
  // TODO: Check signature
  inline void DrawTextLine(SIGNED line, PegPoint point, BOOL fill = FALSE) {
    vft()->DrawTextLine(this, line, fill, 0, point);
  }

  inline PegTextBox_VFTable *vft() {
    return static_cast<PegTextBox_VFTable *>(PegThing_Thin::_vft);
  }

  PEGCHAR *mpBuf;
  PegRect mOldClip;
  SIGNED miClipCount;
  SIGNED miWidestLine;
  SIGNED miLeftOffset;
  SIGNED miTotalLines;
  SIGNED miVisible;
  SIGNED miLineStartTop;
  SIGNED miLineStartEnd;
  SIGNED miLineHeight;
  SIGNED miBufLen;
  SIGNED miHorShift;
  WORD mwMaxChars;
  WORD *mwLineStarts;
  SIGNED miTopLine;
  SIGNED miMarkLine;

  friend class PegTextBox;
  friend class PegEditBox;
};

static_assert(sizeof(PegTextBox_Thin) == 0xac,
              "PegTextBox_Thin has wrong size");

class PegTextBox : public PegWindow, public PegTextThing {
public:
  PegTextBox(PegRect &rect, WORD id = 0,
             WORD style = FF_RECESSED | EF_WRAP | TJ_LEFT,
             const PEGCHAR *text = NULL, WORD maxChars = 1000);

  /**
   * @brief Get the underlying ClassPad object
   * @return ClassPad object
   */
  inline PegTextBox_Thin *obj() {
    return static_cast<PegTextBox_Thin *>(PegWindow::_obj);
  }

  virtual void Append(const PEGCHAR *text, BOOL draw = TRUE);

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegTextBox(PegTextBox_Thin *obj, size_t vftSize);

  virtual void DrawTextLine(SIGNED line, PegPoint point, BOOL fill = FALSE);

private:
  inline PegTextBox_VFTable *vftNew() {
    return static_cast<PegTextBox_VFTable *>(PegWindow::_vftNew);
  }
  inline PegTextBox_VFTable *vftOld() {
    return static_cast<PegTextBox_VFTable *>(PegWindow::_vftOld);
  }
};

extern "C" PegTextBox_Thin *PegTextBox_ctor(PegTextBox_Thin *, PegRect *, WORD,
                                            WORD, const PEGCHAR *, WORD);
