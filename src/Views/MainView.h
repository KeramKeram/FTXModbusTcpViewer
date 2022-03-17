#pragma once
#include "IView.h"

#include <functional>
#include <memory>
#include <cstdlib>
#include <string>
#include <tuple>
#include <thread>
#include <utility>
#include <vector>

#include "Configuration.h"
#include "ModbusModel.h"
#include "ViewCallbacks.h"

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
  MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel, common::ControllerCallbacks &controllerCallbacks,
           configuration::ViewConfiguration &viewConfiguration);

  ~MainView() override;

  void show() override;

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
    std::string mRegisterAddress;
    std::string mRegisterValue;

    Component mSliderX;
    Component mSliderY;
    Component mRadioBoxReg;
    Component mQuitButton;
    Component mInputRegAddress;
    Component mInputRegValue;
    Component mSetRegisterButton;
  };

  Element makeGrid(int registersType);

  Component createRenderer();

  std::shared_ptr<model::ModbusModel> mModbusModel;
  common::ControllerCallbacks &mControllerCallbacks;
  configuration::ViewConfiguration &mViewConfiguration;
  std::thread mRefreshThread;
  std::atomic<bool> mStopInternalThreads;
  Element mGrid;
  UiInternalElements mUiElements;
};
}  // namespace views