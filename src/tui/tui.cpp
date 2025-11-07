#include "tui/tui.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>

using namespace ftxui;
struct tuiState {
  bool showLeft = false;
  bool showMiddle = true;
  bool showRight = false;
};
void tui() {
  tuiState state;
  auto screen = ScreenInteractive::Fullscreen();

  std::string command;

  auto input = Input(&command, "> ");

  auto inputRenderer = Renderer(
      input, [&] { return window(text("Command Prompt"), input->Render()); });

  auto mainPanels = Renderer([&] {
    std::vector<Element> panels{};

    std::vector<Element> horizontalPanels;
    if (state.showLeft)
      horizontalPanels.push_back(text("Left Panel") | border | flex);
    if (state.showMiddle)
      horizontalPanels.push_back(text("Middle Panel") | border | flex);
    if (state.showRight)
      horizontalPanels.push_back(text("Right Panel") | border | flex);

    Element content;
    if (!horizontalPanels.empty())
      content = hbox(horizontalPanels) | flex;
    else
      content = text("No panels visible") | center | flex;

    return content;
  });

  auto root = Container::Vertical({mainPanels, inputRenderer});

  auto component = CatchEvent(root, [&](Event event) {
    if (event == Event::Character('q')) {
      screen.ExitLoopClosure()();
      return true;
    }
    if (event == Event::Character('1')) {
      state.showLeft = !state.showLeft;
      return true;
    }
    if (event == Event::Character('2')) {
      state.showMiddle = !state.showMiddle;
      return true;
    }
    if (event == Event::Character('3')) {
      state.showRight = !state.showRight;
      return true;
    }
    if (event == Event::Character('/')) {
      inputRenderer->TakeFocus();
      return true;
    }
    if (inputRenderer->Focused()) {
      if (event == Event::Escape) {
        mainPanels->TakeFocus();
        return true;
      }
    }
    return false;
  });

  screen.Loop(component);
}
