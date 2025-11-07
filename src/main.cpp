#include <appdef.h>
#include <sdk/os/debug.h>

#include "os/gui/pdecwin.hpp"
#include "os/gui/pegtypes.hpp"
#include "os/gui/ptextbox.hpp"
#include "os/gui/ptitle.hpp"

APP_NAME("Why C++")
APP_AUTHOR("snudget")
APP_DESCRIPTION("Holy description")
APP_VERSION("0.1.0")

class MyWindow : public PegDecoratedWindow {

public:
  MyWindow(PegRect &rect) : PegDecoratedWindow(rect) {
    auto title = new PegTitle("Testle3", TF_CLOSEBUTTON);
    Add(title->obj());

    PegRect textRect;
    textRect.SetAndCenterIfLandscape(40, 80, 300, 105, TRUE);
    auto textBox = new PegTextBox(textRect, 0, FF_NONE | EF_WRAP | TJ_LEFT,
                                  "Hello World!");
    Add(textBox->obj());
  }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {
  // PegRect rectWin(0, 0, 319, 319);
  PegRect rectWin(20, 20, 300, 300);

  auto win = new MyWindow(rectWin);
  win->Execute();

  // Debug_WaitKey();
}
