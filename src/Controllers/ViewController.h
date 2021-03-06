#pragma once

#include <atomic>
#include <memory>

#include "RegisterType.h"
#include "MainView.h"
#include "ModbusModel.h"
#include "ModbusWriter.h"
#include "ControllerCallbacks.h"

namespace controllers {

class ViewController
{
public:
  ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel, const std::shared_ptr<views::IView> &mMainView,
                 const std::shared_ptr<modbusCommon::ModbusWriter> &modbusWriter, common::ControllerCallbacks &callbacks);

  virtual ~ViewController() = default;

  void showView();

  void updateModel(common::RegisterType regType, model::dataPair &registerWithValue);

  unsigned int getCurrentModelView();

  void updateView();

  bool setHoldingRegister(uint16_t address, uint16_t value);

  bool setCoilRegister(uint16_t address, bool value);

  void showConnectionError(std::string error);

private:
  void updateSelectedModel(int selected);

  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::shared_ptr<views::IView> mMainView;
  std::shared_ptr<modbusCommon::ModbusWriter> mModbusWriter;
  std::atomic<int> mSelectedModel;
};
}  // namespace controllers
