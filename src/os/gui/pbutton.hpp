#pragma once

#include "pegtypes.hpp"
#include "pfonts.hpp"
#include "pthing.hpp"
#include "util.hpp"
#include <cstdint>

enum PegButtonSignals {
  PSF_CLICKED = 8,
  PSF_CHECK_ON,
  PSF_CHECK_OFF,
  PSF_DOT_ON,
  PSF_DOT_OFF,
  PSF_LIST_SELECT
};

// **************** //
// *    Button    * //
// **************** //

struct PegButton_VFTable : PegThing_VFTable {};

static_assert(sizeof(PegButton_VFTable) == 0x180,
              "PegButton_VFTable has wrong size");

struct PegButton_Thin : PegThing_Thin {
  inline PegButton_VFTable *vft() {
    return static_cast<PegButton_VFTable *>(_vft);
  }
};

static_assert(sizeof(PegButton_Thin) == 0x50, "PegButton_Thin has wrong size");

class PegButton : public PegThing {
public:
  PegButton(const PegRect &rect, WORD id = 0, WORD flags = AF_ENABLED);
  PegButton(WORD id = 0, WORD flags = AF_ENABLED);

  inline PegButton_Thin *obj() { return static_cast<PegButton_Thin *>(_obj); }

protected:
  PegButton(PegButton_Thin *inner, size_t vftSize);

private:
  inline PegButton_VFTable *vftNew() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftNew);
  }
  inline PegButton_VFTable *vftOld() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftOld);
  }
};

// **************** //
// * Text Button  * //
// **************** //

struct PegTextButton_VFTable : PegThing_VFTable {};

static_assert(sizeof(PegTextButton_VFTable) == 0x180,
              "PegTextButton_VFTable has wrong size");

struct PegTextButton_Thin : PegButton_Thin, PegTextThing_Thin {
  uint32_t unknown_64;

  inline PegTextButton_VFTable *vft() {
    return static_cast<PegTextButton_VFTable *>(PegButton_Thin::_vft);
  }
};

static_assert(sizeof(PegTextButton_Thin) == 0x68,
              "PegTextButton_Thin has wrong size");

class PegTextButton : public PegButton, public PegTextThing {
public:
  PegTextButton(PegRect &rect, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  PegTextButton(SIGNED x, SIGNED y, SIGNED w, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  PegTextButton(SIGNED x, SIGNED y, const PEGCHAR *text, WORD id = 0,
                WORD style = AF_ENABLED | TJ_LEFT, COLORVAL color = 0xFFFF);

  inline PegTextButton_Thin *obj() {
    return static_cast<PegTextButton_Thin *>(PegButton::_obj);
  }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegTextButton(PegTextButton_Thin *obj, size_t vftSize);

private:
  inline PegButton_VFTable *vftNew() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftNew);
  }
  inline PegButton_VFTable *vftOld() {
    return static_cast<PegButton_VFTable *>(PegThing::_vftOld);
  }
};

// **************** //
// * Radio Button * //
// **************** //

struct PegRadioButton_VFTable : PegButton_VFTable {
  VFTableFunction<void, BOOL> SetSelected;
  VFTableFunction<BOOL> IsSelected;
};

static_assert(sizeof(PegRadioButton_VFTable) == 0x198,
              "PegRadioButton_VFTable has wrong size");

struct PegRadioButton_Thin : PegButton_Thin, PegTextThing_Thin {
  uint32_t unknown_64;

  VFT_FORWARD(SetSelected, void, (BOOL select = TRUE), (select))
  VFT_FORWARD(IsSelected, BOOL, (), ())

  inline PegRadioButton_VFTable *vft() {
    return static_cast<PegRadioButton_VFTable *>(PegButton_Thin::_vft);
  }
};

static_assert(sizeof(PegRadioButton_Thin) == 0x68,
              "PegRadioButton_Thin has wrong size");

class PegRadioButton : public PegButton, public PegTextThing {
public:
  PegRadioButton(SIGNED x, SIGNED y, const PEGCHAR *text, WORD id = 0,
                 WORD style = AF_ENABLED, PegFont *font = NULL,
                 BOOL unknown = TRUE);

  PegRadioButton(PegRect &rect, const PEGCHAR *text, WORD id = 0,
                 WORD style = AF_ENABLED);

  virtual void SetSelected(BOOL select = TRUE);
  virtual BOOL IsSelected();

  inline PegRadioButton_Thin *obj() {
    return static_cast<PegRadioButton_Thin *>(PegButton::_obj);
  }

protected:
  /**
   * @brief Internal constructor that wraps a ClassPad object.
   * @param obj ClassPad object to wrap.
   * @param vftSize Size of the derived VFT.
   */
  PegRadioButton(PegRadioButton_Thin *obj, size_t vftSize);

private:
  inline PegRadioButton_VFTable *vftNew() {
    return static_cast<PegRadioButton_VFTable *>(PegThing::_vftNew);
  }
  inline PegRadioButton_VFTable *vftOld() {
    return static_cast<PegRadioButton_VFTable *>(PegThing::_vftOld);
  }
};
