#pragma once

#include <atomic>
#include <memory>

#include "RegisterType.h"
#include "MainView.h"
#include "ModbusModel.h"

namespace controllers {

class ViewController
{
public:
  ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel, const std::shared_ptr<views::IView> &mMainView);

  virtual ~ViewController() = default;

  void showView();

  void updateModel(common::RegisterType regType, model::dataPair &registerWithValue);

  unsigned int getCurrentModelView();

  void updateView();

private:
  void updateSelectedModel(int selected);

  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::shared_ptr<views::IView> mMainView;

  std::atomic<int> mSelectedModel;
};
}  // namespace controllers
