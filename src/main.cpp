#include <appdef.h>

// Include
#include "os/gui/peg.hpp"

APP_NAME("Peg example")
APP_AUTHOR("snudget")
APP_DESCRIPTION("A simple Click Me example")
APP_VERSION("0.5.0")

class MyWindow : public PegDecoratedWindow {
  // Auto-generate element ids, so we don't have to manually set them
  enum Ids {
    Id_TextBox = 1,
    Id_Button,
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
    textRect.SetAndCenterIfLandscape(40, 80, 300, 105, TRUE);
    textBox = new PegTextBox(textRect, Id_TextBox, FF_NONE | EF_WRAP | TJ_LEFT,
                             "Hello World!");

    // Again, absolute coordinates
    PegRect buttonRect;
    buttonRect.SetAndCenterIfLandscape(40, 120, 120, 160, TRUE);
    auto button = new PegTextButton(buttonRect, "Press Me!", Id_Button);

    // Elements need to be added to a container (our window body)
    Add(title->obj());
    Add(textBox->obj());
    Add(button->obj());
  }

  // This function receives events like button clicks
  // Overrides will be inserted into the inner vftable
  SIGNED Message(const PegMessage &mesg) override {
    switch (mesg.wType) {
    // Here we can switch over all the events that UI elements can produce
    case PEG_SIGNAL(Id_Button, PSF_CLICKED):

      // Chage the contents of our checkbox
      textBox->DataSet("Button pressed!");
      // The screen will only draw previously invalidated regions
      Screen()->Invalidate(textBox->obj()->mClip);
      // Trigger a redraw
      textBox->Draw();

      // Consume the event.
      return 0;
    }

    // We still want events like the close button to be handled
    return PegDecoratedWindow::Message(mesg);
  }

private:
  // Store the textbox so we can change its contents
  PegTextBox *textBox;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {
  // Set the dimensions of our window
  PegRect rectWin(20, 20, 300, 300);
  auto win = new MyWindow(rectWin);

  // Show the window. This will also delete all the elements when it is closed
  win->Execute();
  // But it won't delete the wrapper class
  // WARNING: This may change in the future, not sure yet
  delete win;
}