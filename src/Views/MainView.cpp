#include "MainView.h"
#include <string>
#include <vector>
#include "TableCreator.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

namespace views {
using namespace ftxui;

MainView::MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel, common::ControllerCallbacks &controllerCallbacks,
                   configuration::ViewConfiguration &viewConfiguration)
  : mModbusModel(mModbusModel)
  , mControllerCallbacks(controllerCallbacks)
  , mViewConfiguration(viewConfiguration)
  , mStopInternalThreads(false)
{
}

MainView::~MainView()
{
  mStopInternalThreads.store(true);
  if (mRefreshThread.joinable()) { mRefreshThread.join(); }
}

void MainView::show()
{
  mUiElements.mSliderX                   = Slider("x", &mUiElements.mFocusX, 0.f, 1.f, 0.01f);
  mUiElements.mSliderY                   = Slider("y", &mUiElements.mFocusY, 0.f, 1.f, 0.01f);
  std::vector<std::string> radiobox_list = {
    "Coils",
    "Input status",
    "Input Register",
    "Holding Register",
  };
  mUiElements.mRadioBoxReg = Radiobox(&radiobox_list, &mUiElements.mSelectedRegister);

  mControllerCallbacks.mUpdateSelectedModel(mUiElements.mSelectedRegister);
  mGrid = makeGrid(mUiElements.mSelectedRegister);

  auto screen                                           = ScreenInteractive::Fullscreen();
  mUiElements.mQuitButton                               = Button("Quit", screen.ExitLoopClosure());
  mUiElements.mInputRegAddress                          = Input(&mUiElements.mRegisterAddress, "0");
  mUiElements.mInputRegValue                            = Input(&mUiElements.mRegisterValue, "0");
  mUiElements.mSetRegisterButton                               = Button("Set Reg.", [this] { });
  Component renderer                                    = createRenderer();

  mStopInternalThreads.store(false);
  std::thread refresh_ui([&, this] {
    while (!mStopInternalThreads) {
      if (mUiElements.mRefreshUI.load() || (mUiElements.mPreviousSelectedRegister != mUiElements.mSelectedRegister)) {
        mUiElements.mPreviousSelectedRegister = mUiElements.mSelectedRegister;
        mControllerCallbacks.mUpdateSelectedModel(mUiElements.mSelectedRegister);
        mUiElements.mRefreshUI.store(false);
        mGrid = makeGrid(mUiElements.mSelectedRegister);
        screen.PostEvent(Event::Custom);
      }
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.1s);
    }
  });

  mRefreshThread = std::move(refresh_ui);

  screen.Loop(renderer);
}

Element MainView::makeGrid(int registersType)
{
  std::vector<std::string> vals;
  switch (registersType) {
  case 0: vals = mModbusModel->getAllValuesForCoils(); break;
  case 1: vals = mModbusModel->getAllValuesForInputStatus(); break;
  case 2: vals = mModbusModel->getAllValuesForInputRegisters(); break;
  case 3: vals = mModbusModel->getAllValuesForHoldingRegisters(); break;
  default: break;
  }
  TableCreator factory(mViewConfiguration);
  auto output = factory.createTable(vals);
  return gridbox(output);
}

Component MainView::createRenderer()
{
  auto renderer = Renderer(Container::Vertical({ mUiElements.mRadioBoxReg,
                                                 mUiElements.mSliderX,
                                                 mUiElements.mSliderY,
                                                 mUiElements.mQuitButton,
                                                 mUiElements.mInputRegAddress,
                                                 mUiElements.mInputRegValue }),
                           [&, this] {
                             auto title = "focusPositionRelative(" +                    //
                                          std::to_string(mUiElements.mFocusX) + ", " +  //
                                          std::to_string(mUiElements.mFocusY) + ")";    //
                             return vbox({ text(title),
                                           separator(),
                                           mUiElements.mRadioBoxReg->Render(),
                                           mUiElements.mSliderX->Render(),
                                           mUiElements.mSliderY->Render(),
                                           hbox(text(" Reg. Address : "), mUiElements.mInputRegAddress->Render()),
                                           hbox(text(" Reg. Value : "), mUiElements.mInputRegValue->Render()),
                                           mUiElements.mSetRegisterButton->Render(),
                                           mUiElements.mQuitButton->Render(),
                                           separator(),
                                           mGrid | focusPositionRelative(mUiElements.mFocusX, mUiElements.mFocusY) | frame | flex })
                                    | border;
                           });
  return renderer;
}

void MainView::updateView()
{
  mUiElements.mRefreshUI.store(true);
}

}  // namespace views