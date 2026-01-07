#include <appdef.h>

#include <sdk/os/debug.h>
#include <sdk/os/lcd.h>

#include "os/gui/peg.hpp"

APP_NAME("PegEditBox Demo")
APP_AUTHOR("snudget, pho3")
APP_DESCRIPTION("PegVertList and PegEditBox")
APP_VERSION("1.1.0")

const WORD TEXTBOX_STYLE = FF_NONE | EF_WRAP | TJ_LEFT;

class MyWindow : public PegDecoratedWindow {
  // Auto-generate element ids, so we don't have to manually set them
  enum Ids {
    Id_InfoText = 1,
    Id_List,
    Id_Opt_1,
    Id_Opt_2,
    Id_Opt_3,
    Id_Opt_4,
    Id_Btn,
    Id_EditBox // New ID for edit box
  };

public:
  MyWindow(PegRect &rect) : PegDecoratedWindow(rect) {
    // This is the title bar of our window. Remember to add it, or you won't be
    // able to close it
    auto title = new PegTitle("Testle3", TF_CLOSEBUTTON);

    // These are absolute coordinates.
    // Since our window starts at x=20, this will give 20 pixels of padding
    // This method will also recalculate the positions in horizontal mode
    PegRect textRect;
    textRect.SetAndCenterIfLandscape(20, 30, 300, 60, TRUE);
    infoBox = new PegTextBox(textRect, Id_InfoText, TEXTBOX_STYLE,
                             "Select an option below...");

    Add(title->obj());
    Add(infoBox->obj());

    // Define the List Area
    // The list will occupy this specific rectangle.
    // If items exceed this area, it should scroll (if scrollbars enabled/auto).
    PegRect listRect;
    listRect.SetAndCenterIfLandscape(20, 70, 150, 180, TRUE); // Left side

    // Create the Vertical List
    // FF_THIN: Draws a thin border around the list
    vertList = new PegVertList(listRect, Id_List, FF_THIN);

    options[0] = new PegRadioButton(0, 0, "Option 1", Id_Opt_1);
    options[1] = new PegRadioButton(0, 0, "Option 2", Id_Opt_2);
    options[2] = new PegRadioButton(0, 0, "Option 3", Id_Opt_3);
    options[3] = new PegRadioButton(0, 0, "Option 4", Id_Opt_4);

    // Add Items to the List
    // We pass the underlying thin object via ->obj()
    for (auto item : options) {
      vertList->Add(item->obj());
    }

    // Select first option
    options[0]->SetSelected();
    vertList->SetSelected(options[0]->obj()); // Using wrapper helper
    Add(vertList->obj());

    // 3. PegEditBox (Editable Text Area)
    // Placed to the right of the list or below depending on space.
    // Here placing it to the right side (Landscape logic assumed mostly)
    PegRect editRect;
    editRect.SetAndCenterIfLandscape(160, 70, 300, 180, TRUE);

    mpEditBox =
        new PegEditBox(editRect, Id_EditBox, FF_RECESSED | EF_EDIT | EF_WRAP);

    // Set initial text
    mpEditBox->DataSet("Type here...\nLine 2");

    // Enable vertical scrollbar automatically when text exceeds height
    mpEditBox->SetScrollMode(WSM_AUTOVSCROLL | WSM_CONTINUOUS);

    Add(mpEditBox->obj());

    // 4. Select Button
    PegRect buttonRect;
    buttonRect.SetAndCenterIfLandscape(110, 200, 210, 230, TRUE);
    auto button =
        new PegTextButton(buttonRect, "Check", Id_Btn, AF_ENABLED | TJ_CENTER);
    Add(button->obj());
  }

  SIGNED Message(const PegMessage &mesg) override {
    const char *strings[4] = {
        "Opt 1",
        "Opt 2",
        "Opt 3",
        "Opt 4",
    };

    // All events can be handled in a single switch
    switch (mesg.wType) {
    // Detect select button click
    case PEG_SIGNAL(Id_Btn, PSF_CLICKED):
      // On button click, we update the status box with current selection
      // AND append some text to the EditBox to demonstrate API usage.

      infoBox->DataSet("Processing...");

      for (int i = 0; i < 4; i++) {
        if (options[i]->IsSelected()) {
          infoBox->DataSet(strings[i]);

          // Append selection to edit box
          // Note: Append automatically handles redrawing if bDraw is true
          // (default)
          mpEditBox->Append("\nSelected: ");
          mpEditBox->Append(strings[i]);
        }
      }

      Screen()->Invalidate(infoBox->obj()->mClip);

      // Redraw the text
      infoBox->Draw();
      return 0;
    }

    // We still want events like the close button to be handled
    return PegDecoratedWindow::Message(mesg);
  }

private:
  PegTextBox *infoBox;
  PegVertList *vertList;
  PegRadioButton *options[4];
  PegEditBox *mpEditBox; // Pointer to our new EditBox
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {
  // Make window slightly larger to fit everything nicely
  PegRect rectWin(10, 10, 310, 280);
  auto win = new MyWindow(rectWin);

  // Show the window. This will also delete all the elements when it is closed
  win->Execute();
  // But it won't delete the wrapper class
  // WARNING: This may change in the future, not sure yet
  delete win;
}
