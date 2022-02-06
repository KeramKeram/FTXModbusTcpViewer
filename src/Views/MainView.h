#pragma once
#include "IView.h"

#include <memory>    // for allocator, __shared_ptr_access
#include <stdlib.h>  // for EXIT_SUCCESS
#include <string>    // for string, operator+, basic_string, to_string, char_traits
#include <utility>
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                  // for text, Element, operator|, window, flex, vbox
#include "ModbusModel.h"

namespace views {
using namespace ftxui;

/*constexpr int VIEW_COLUMNS    = 2;
constexpr int VIEW_ROWS       = 2;
constexpr int VIEW_BOX_WIDTH  = 8;
constexpr int VIEW_BOX_HEIGHT = 3;*/

class MainView : public IView
{
public:
  MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel);

  ~MainView() override = default;

  void show() override;

private:
  Element mGrid;

public:
  void updateView() override;

private:
  Element makeGrid(int registersType);
  Component createRenderer(float focus_x, float focus_y, Component &slider_x, Component &slider_y, Component &radiobox);
  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::atomic_bool mRefreshUI{};
  int mSelectedRegister;
  int mPreviousSelectedRegister;
};
}  // namespace views