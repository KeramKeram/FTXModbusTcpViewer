#pragma once
#include "IView.h"

#include <functional>
#include <memory>
#include <cstdlib>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "Configuration.h"
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
  MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel, std::function<void(int)> updateselectedModel,
           configuration::ViewConfiguration &viewConfiguration);

  ~MainView() override;

  void show() override;

private:
  Element mGrid;

public:
  void updateView() override;
  void setSelectedModel(std::function<void(int)> func) override;

private:
  struct UiInternalElements
  {
    std::atomic_bool mRefreshUI{};
    int mSelectedRegister{ 0 };
    int mPreviousSelectedRegister{ 0 };
    float mFocusX{ 0 };
    float mFocusY{ 0 };
  };

  Element makeGrid(int registersType);
  Component createRenderer(Component &slider_x, Component &slider_y, Component &radiobox, Component &qButton);


  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::function<void(int)> mUpdateSelectedModel;
  configuration::ViewConfiguration &mViewConfiguration;
  std::thread mRefreshThread;
  std::atomic<bool> mStopInternalThreads;
  UiInternalElements mUiElements;
};
}  // namespace views