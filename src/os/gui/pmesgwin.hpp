#pragma once

#include "pegtypes.hpp"
#include "pfonts.hpp"
#include "pwindow.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>

enum MessageWindowTypeEnum {
  ERROR_WINDOW,
  TWO_SECTION_WINDOW,
  LAST_MESSAGE_WINDOW_TYPE,
};

struct PegMessageWindow_VFTable : PegWindow_VFTable {
  VFTableFunction<WORD> Style2_0;
  VFTableFunction<void, WORD> Style2_1;
};

static_assert(sizeof(PegMessageWindow_VFTable) == 0x21C,
              "PegMessageWindow_VFTable has wrong size");

struct PegMessageWindow_VFTable_PegTextThing : PegWindow_VFTable {};

struct PegMessageWindow_Thin : PegWindow_Thin, PegTextThing_Thin {
public:
  VFT_FORWARD_TO(Style2, Style2_0, WORD, (), ())
  VFT_FORWARD_TO(Style2, Style2_1, void, (WORD style), (style))

protected:
  void *mpTitle;
  PegThing *mpOwner;
  void *mpIcon;
  SIGNED miButtonWidth;
  SIGNED miOneButtonWidth;
  SIGNED miMessageWidth;
  PEGCHAR *mpMessage;
  PEGCHAR *mpComment;
  SIGNED miCommentWidth;
  SIGNED miMessageHeight;
  SIGNED miCommentHeight;
  WORD mwStyle2;
  uint32_t _m_action_keys[3];
  WORD _unknown;

  inline PegMessageWindow_VFTable *vft() {
    return static_cast<PegMessageWindow_VFTable *>(PegWindow_Thin::_vft);
  }
};

static_assert(sizeof(PegMessageWindow_Thin) == 0xb4,
              "PegMessageWindow_Thin has wrong size");

class PegMessageWindow : public PegWindow, public PegTextThing {
public:
  PegMessageWindow(const PEGCHAR *title, const PEGCHAR *message = NULL,
                   WORD style = MW_ESC | FF_RAISED, WORD style2 = 0,
                   void *icon = NULL, PegThing *owner = NULL);
  PegMessageWindow(const PEGCHAR *title, const PEGCHAR *message,
                   const PEGCHAR *comment, WORD style, WORD style2, void *pIcon,
                   WORD unknown, MessageWindowTypeEnum type = ERROR_WINDOW);

  inline PegMessageWindow_Thin *obj() {
    return static_cast<PegMessageWindow_Thin *>(PegWindow::_obj);
  }

  virtual WORD Style2();
  virtual void Style2(WORD style2);

protected:
  PegMessageWindow(PegMessageWindow_Thin *obj, size_t vftSize);

private:
  inline PegMessageWindow_VFTable *vftNew() {
    return static_cast<PegMessageWindow_VFTable *>(PegWindow::_vftNew);
  }
  inline PegMessageWindow_VFTable *vftOld() {
    return static_cast<PegMessageWindow_VFTable *>(PegWindow::_vftOld);
  }
};

extern "C" PegMessageWindow_Thin *
PegMessageWindow_ctor_0(PegMessageWindow_Thin *, const PEGCHAR *,
                        const PEGCHAR *, WORD, WORD, void *, PegThing *);

extern "C" PegMessageWindow_Thin *
PegMessageWindow_ctor_1(PegMessageWindow_Thin *, const PEGCHAR *,
                        const PEGCHAR *, const PEGCHAR *, WORD, WORD, void *,
                        WORD, MessageWindowTypeEnum);
