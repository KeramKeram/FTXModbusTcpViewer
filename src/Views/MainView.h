#pragma once
#include "IView.h"

#include <functional>
#include <memory>
#include <cstdlib>
#include <string>
#include <thread>
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
  MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel, std::function<void(int)> updateselectedModel);

  ~MainView() override;

  void show() override;

private:
  Element mGrid;

public:
  void updateView() override;
  void setSelectedModel(std::function<void(int)> func) override;

private:
  Element makeGrid(int registersType);
  Component createRenderer(Component &slider_x, Component &slider_y, Component &radiobox, Component &qButton);

  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::function<void(int)> mUpdateSelectedModel;
  std::atomic_bool mRefreshUI{};
  int mSelectedRegister;
  int mPreviousSelectedRegister;
  std::thread mRefreshThread;
  std::atomic<bool> mStopInternalThreads;
  float mFocusX;
  float mFocusY;
};
}  // namespace views