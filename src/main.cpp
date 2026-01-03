#include <appdef.h>
#include <cstring>

#include <sdk/os/debug.h>
#include <sdk/os/lcd.h>

#include "os/gui/peg.hpp"

APP_NAME("VertList Demo")
APP_AUTHOR("snudget, pho3")
APP_DESCRIPTION("PegVertList with Radio buttons")
APP_VERSION("1.0.0")

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
    Id_Btn
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
    textRect.SetAndCenterIfLandscape(20, 50, 300, 80, TRUE);
    infoBox = new PegTextBox(textRect, Id_InfoText, TEXTBOX_STYLE,
                             "Select an option below...");

    Add(title->obj());
    Add(infoBox->obj());

    // Define the List Area
    // The list will occupy this specific rectangle.
    // If items exceed this area, it should scroll (if scrollbars enabled/auto).
    PegRect listRect;
    listRect.SetAndCenterIfLandscape(40, 80, 280, 200, TRUE);

    // Create the Vertical List
    // FF_THIN: Draws a thin border around the list
    vertList = new PegVertList(listRect, Id_List, FF_THIN);

    // Create List Items (list handles positioning)
    options[0] = new PegRadioButton(0, 0, "First Option", Id_Opt_1);
    options[1] = new PegRadioButton(0, 0, "Second Option", Id_Opt_2);
    options[2] = new PegRadioButton(0, 0, "Third Option", Id_Opt_3);
    options[3] = new PegRadioButton(0, 0, "Fourth Option", Id_Opt_4);

    // Add Items to the List
    // We pass the underlying thin object via ->obj()
    for (auto item : options) {
      vertList->Add(item->obj());
    }

    // Select first option
    options[0]->SetSelected();
    vertList->SetSelected(options[0]->obj());

    // Add the List to the Window
    Add(vertList->obj());

    // A select button for our list
    PegRect buttonRect(rect.wLeft + 5, rect.wBottom - 40, rect.wLeft + 97,
                       rect.wBottom - 6);
    auto button =
        new PegTextButton(buttonRect, "Select", Id_Btn, AF_ENABLED | TJ_CENTER);

    Add(button->obj());
  }

  // Handle events (like button clicks, keypresses, etc.)
  SIGNED Message(const PegMessage &mesg) override {
    const char *strings[4] = {
        "First Option selected",
        "Second Option selected",
        "Third Option selected",
        "Fourth Option selected",
    };

    // All events can be handled in a single switch
    switch (mesg.wType) {
    // Detect select button click
    case PEG_SIGNAL(Id_Btn, PSF_CLICKED):
      infoBox->DataSet("Nothing selected");
      // Check which radio button is selected
      for (int i = 0; i < 4; i++)
        if (options[i]->IsSelected())
          infoBox->DataSet(strings[i]);

      // Tell the screen what area should be redrawn
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
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {
  PegRect rectWin(10, 10, 310, 280);
  auto win = new MyWindow(rectWin);

  // Show the window. This will also delete all the elements when it is closed
  win->Execute();
  // But it won't delete the wrapper class
  // WARNING: This may change in the future, not sure yet
  delete win;
}
