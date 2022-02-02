#include "MainView.h"
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <thread>
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/component.hpp"           // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                  // for text, Element, operator|, window, flex, vbox


#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Cyan, Color::White

namespace views {
using namespace ftxui;

MainView::MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel)
  : mModbusModel(mModbusModel), mSelectedRegister(0), mPreviousSelectedRegister(0)
{
}

void MainView::show()
{
  float focus_x = 0.0f;
  float focus_y = 0.0f;

  auto slider_x                          = Slider("x", &focus_x, 0.f, 1.f, 0.01f);
  auto slider_y                          = Slider("y", &focus_y, 0.f, 1.f, 0.01f);
  std::vector<std::string> radiobox_list = {
    "Coils",
    "Input status",
    "Input Register",
    "Holding Register",
  };
  auto radiobox = Radiobox(&radiobox_list, &mSelectedRegister);

  mGrid              = makeGrid(mSelectedRegister);
  Component renderer = createRenderer(focus_x, focus_y, slider_x, slider_y, radiobox);

  auto screen = ScreenInteractive::Fullscreen();

  std::thread refresh_ui([&, this] {
    while (true) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.5s);
      if (mRefreshUI.load() || (mPreviousSelectedRegister != mSelectedRegister)) {
        mPreviousSelectedRegister = mSelectedRegister;
        mRefreshUI.store(false);
        mGrid = makeGrid(mSelectedRegister);
        screen.PostEvent(Event::Custom);
      }
    }
  });

  screen.Loop(renderer);
}

Element MainView::makeBox(const BoxParameter &param)
{
  const auto [x, y, value, hue, saturation, hvValue] = param;
  return text(value) | center | size(WIDTH, EQUAL, VIEW_BOX_WIDTH) | size(HEIGHT, EQUAL, VIEW_BOX_HEIGHT) | border
         | bgcolor(Color::HSV(hue, saturation, hvValue));
}

Element MainView::makeGrid(int registersType)
{
  std::vector<std::string> vals;
  switch (registersType) {
  case 0: vals = mModbusModel->getAllValuesForCoils(); break;
  case 1: vals = mModbusModel->getAllValuesForInputStatus(); break;
  case 2: vals = mModbusModel->getAllValuesForInputRegisters(); break;
  case 3: vals = mModbusModel->getAllValuesForHoldingRegisters(); break;
  }
  std::vector<Elements> rows;
  std::string val;
  BoxParameter param(0, 0, "", 0, 255, 0);
  for (int i = 0; i < VIEW_COLUMNS; i++) {
    std::vector<Element> cols;
    param.mXPosition = i;
    for (int j = 0; j < VIEW_ROWS; j++) {
      if (j == 0 && i == 0) {
        updateBoxParameters(param, i, j, 40, 200);
      } else if (j == 0) {
        updateBoxParameters(param, i, j, 85, 100);
      } else if (i == 0 && j >= 1) {
        updateBoxParameters(param, i, j, 0, 0);
      } else {
        updateBoxParameters(param, i, j, 185, 100);
      }
      cols.push_back(makeBox(param));
    }
    rows.push_back(cols);
  }

  return gridbox(rows);
}
void MainView::updateBoxParameters(MainView::BoxParameter &param, int i, int j, int hue, int hsv)
{
  param.mYPosition = j;
  param.mBoxValue  = std::to_string(j);
  param.mHue       = hue;
  param.mHSVValue  = hsv;
}

Component MainView::createRenderer(float focus_x, float focus_y, Component &slider_x, Component &slider_y, Component &radiobox)
{
  auto renderer = Renderer(Container::Vertical({
                             radiobox,
                             slider_x,
                             slider_y,
                           }),
                           [&, this] {
                             auto title = "focusPositionRelative(" +        //
                                          std::to_string(focus_x) + ", " +  //
                                          std::to_string(focus_y) + ")";    //
                             return vbox({
                                      text(title),
                                      separator(),
                                      radiobox->Render(),
                                      slider_x->Render(),
                                      slider_y->Render(),
                                      separator(),
                                      mGrid | focusPositionRelative(focus_x, focus_y) | frame | flex,
                                    })
                                    | border;
                           });
  return renderer;
}

void MainView::updateView()
{
  mRefreshUI.store(true);
}
}  // namespace views