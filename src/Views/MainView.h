#pragma once
#include "IView.h"

#include <memory>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>

#include "ModbusModel.h"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

namespace views {
using namespace ftxui;

class MainView : public IView
{
public:
  explicit MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel);

  ~MainView() override = default;

  void show() override;

private:
  Element mGrid;

public:
  void updateView() override;

private:
  Element makeGrid(int registersType);
  Component createRenderer(float focus_x, float focus_y, Component &slider_x, Component &slider_y, Component &radiobox, Component &qButton);
  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::atomic_bool mRefreshUI{};
  int mSelectedRegister;
  int mPreviousSelectedRegister;
};
}  // namespace views