#include "MainView.h"
#include <string>
#include <vector>
#include "TableCreator.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

namespace views {
using namespace ftxui;

MainView::MainView(const std::shared_ptr<model::ModbusModel> &mModbusModel, std::function<void(int)> updateselectedModel,
                   configuration::ViewConfiguration &viewConfiguration)
  : mModbusModel(mModbusModel)
  , mUpdateSelectedModel(updateselectedModel)
  , mViewConfiguration(viewConfiguration)
  , mSelectedRegister(0)
  , mPreviousSelectedRegister(0)
  , mStopInternalThreads(false)
  , mFocusX(0)
  , mFocusY(0)
{
}

MainView::~MainView()
{
  mStopInternalThreads.store(true);
  if (mRefreshThread.joinable()) { mRefreshThread.join(); }
}

void MainView::show()
{
  auto slider_x                          = Slider("x", &mFocusX, 0.f, 1.f, 0.01f);
  auto slider_y                          = Slider("y", &mFocusY, 0.f, 1.f, 0.01f);
  std::vector<std::string> radiobox_list = {
    "Coils",
    "Input status",
    "Input Register",
    "Holding Register",
  };
  auto radiobox = Radiobox(&radiobox_list, &mSelectedRegister);

  mUpdateSelectedModel(mSelectedRegister);
  mGrid = makeGrid(mSelectedRegister);

  auto screen        = ScreenInteractive::Fullscreen();
  auto buttonQ       = Button("Quit", screen.ExitLoopClosure());
  Component renderer = createRenderer(slider_x, slider_y, radiobox, buttonQ);

  mStopInternalThreads.store(false);
  std::thread refresh_ui([&, this] {
    while (!mStopInternalThreads) {
      if (mRefreshUI.load() || (mPreviousSelectedRegister != mSelectedRegister)) {
        mPreviousSelectedRegister = mSelectedRegister;
        mUpdateSelectedModel(mSelectedRegister);
        mRefreshUI.store(false);
        mGrid = makeGrid(mSelectedRegister);
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

Component MainView::createRenderer(Component &slider_x, Component &slider_y, Component &radiobox, Component &qButton)
{
  auto renderer = Renderer(Container::Vertical({ radiobox, slider_x, slider_y, qButton }), [&, this] {
    auto title = "focusPositionRelative(" +        //
                 std::to_string(mFocusX) + ", " +  //
                 std::to_string(mFocusY) + ")";    //
    return vbox({ text(title),
                  separator(),
                  radiobox->Render(),
                  slider_x->Render(),
                  slider_y->Render(),
                  qButton->Render(),
                  separator(),
                  mGrid | focusPositionRelative(mFocusX, mFocusY) | frame | flex })
           | border;
  });
  return renderer;
}

void MainView::updateView()
{
  mRefreshUI.store(true);
}

void MainView::setSelectedModel(std::function<void(int)> func)
{
  mUpdateSelectedModel = std::move(func);
}

}  // namespace views