#include "tui/tui.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>

#include "tui/parser.h"

using namespace ftxui;

struct tuiState {
  bool showLeft = false;
  bool showMiddle = true;
  bool showRight = false;
};

void tui() {
  tuiState state;
  TuiOptions commandState;
  auto screen = ScreenInteractive::Fullscreen();

  std::string command;

  auto input = Input(&command, "> ");

  auto inputRenderer = Renderer(
      input, [&] { return window(text("Command Prompt"), input->Render()); });

  auto mainPanels = Renderer([&] {
    std::vector<Element> panels{};
    if (state.showLeft)
      // if left panel is active while orders search, present the query for the
      // orders here.
      panels.push_back(window(text("[1] Item"), text(commandState.output)) |
                       flex);
    if (state.showMiddle)
      // orders results goes here.
      panels.push_back(window(text("[2] Orders"), text("TODO")) | flex);
    if (state.showRight)
      // TODO: once ocr is implemented, store history of items here
      panels.push_back(window(text("[3] Recent Items"), text("TODO")) | flex);
    if (panels.empty()) return text("No panels visible") | center | flex;
    return hbox(std::move(panels)) | flex;
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
    if (event == Event::Return) {
      processTuiArgs(command, commandState);
      handleTuiArgs(commandState);
      mainPanels->TakeFocus();
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
