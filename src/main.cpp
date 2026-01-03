#include <appdef.h>

// Include
#include "os/gui/peg.hpp"
#include "os/gui/pegtypes.hpp"

APP_NAME("VertList Demo")
APP_AUTHOR("snudget")
APP_DESCRIPTION("PegVertList with Buttons")
APP_VERSION("1.0.0")

class MyWindow : public PegDecoratedWindow {
  // Auto-generate element ids, so we don't have to manually set them
  enum Ids { Id_InfoText = 1, Id_List, Id_Btn_1, Id_Btn_2, Id_Btn_3, Id_Btn_4 };

public:
  MyWindow(PegRect &rect) : PegDecoratedWindow(rect) {
    // This is the title bar of our window. Remember to add it, or you won't be
    // able to close it
    auto title = new PegTitle("Testle3", TF_CLOSEBUTTON);

    // These are absolute coordinates.
    // Since our window starts at x=20, this will give 20 pixels of padding
    // This method will also recalculate the positions in horizontal mode
    PegRect textRect;
    textRect.SetAndCenterIfLandscape(20, 40, 300, 70, TRUE);
    infoBox =
        new PegTextBox(textRect, Id_InfoText, FF_RECESSED | EF_WRAP | TJ_LEFT,
                       "Select an option below...");

    Add(title->obj());
    Add(infoBox->obj());

    // 2. Define the List Area
    // The list will occupy this specific rectangle.
    // If items exceed this area, it should scroll (if scrollbars enabled/auto).
    PegRect listRect;
    listRect.SetAndCenterIfLandscape(40, 80, 280, 200, TRUE);

    // 3. Create the Vertical List
    // FF_THIN: Draws a thin border around the list
    // The constructor implementation must exist in plist.cpp
    vertList = new PegVertList(listRect, Id_List, FF_THIN);

    // 4. Create List Items (Buttons)
    // IMPORTANT: For PegVertList, only the HEIGHT of the item rect matters.
    // The Left, Top, and Width are calculated by the list automatically.
    // We set height to 30 pixels here.
    PegRect itemRect;
    itemRect.Set(0, 0, 100, 30);

    // Create buttons with the same rect (list handles positioning)
    auto btn1 = new PegTextButton(itemRect, "First Option", Id_Btn_1);
    auto btn2 = new PegTextButton(itemRect, "Second Option", Id_Btn_2);
    auto btn3 = new PegTextButton(itemRect, "Third Option", Id_Btn_3);
    auto btn4 = new PegTextButton(itemRect, "Fourth Option", Id_Btn_4);

    // 5. Add Items to the List
    // We pass the underlying thin object via ->obj()
    vertList->Add(btn1->obj());
    vertList->Add(btn2->obj());
    vertList->Add(btn3->obj());
    vertList->Add(btn4->obj());

    // Optional: Select the first item by default
    vertList->SetSelected((SIGNED)0);

    // 6. Add the List to the Window
    Add(vertList->obj());
  }

  // Handle Signals
  SIGNED Message(const PegMessage &mesg) override {
    switch (mesg.wType) {

    // Catch the List Selection Change Signal
    // This is fired when the user navigates the list (up/down) or clicks an
    // item.
    case PEG_SIGNAL(Id_List, PSF_LIST_SELECT): {
      // Get the ID of the currently selected item
      // Since we don't have GetSelectedId mapped, we can get the object and
      // check its ID
      PegThing_Thin *selected = vertList->GetSelected();
      if (selected) {
        WORD id = selected->Id();

        if (id == Id_Btn_1)
          infoBox->DataSet("Option 1 Selected");
        else if (id == Id_Btn_2)
          infoBox->DataSet("Option 2 Selected");
        else if (id == Id_Btn_3)
          infoBox->DataSet("Option 3 Selected");
        else if (id == Id_Btn_4)
          infoBox->DataSet("Option 4 Selected");

        // Redraw the textbox to show change
        infoBox->Draw();
      }
      return 0;
    }

    // You can also catch specific button clicks if needed
    // But typically in a list, you handle the selection or an "Enter" key press
    // on the list.
    case PEG_SIGNAL(Id_Btn_4, PSF_CLICKED):
      infoBox->DataSet("Button 4 Clicked!");
      infoBox->Draw();
      return 0;
    }

    // We still want events like the close button to be handled
    return PegDecoratedWindow::Message(mesg);
  }

private:
  PegTextBox *infoBox;
  PegVertList *vertList;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {
  PegRect rectWin(10, 10, 310, 230);
  auto win = new MyWindow(rectWin);

  // Show the window. This will also delete all the elements when it is closed
  win->Execute();
  // But it won't delete the wrapper class
  // WARNING: This may change in the future, not sure yet
  delete win;
}
