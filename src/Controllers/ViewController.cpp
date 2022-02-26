#include "ViewController.h"
#include <iostream>
namespace controllers {
ViewController::ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel, const std::shared_ptr<views::IView> &mMainView)
  : mModbusModel(mModbusModel), mMainView(mMainView)
{
  mModbusModel->setUpdateCallback([this]() { updateView(); });
}

void ViewController::showView()
{
  mMainView->show();
}

void ViewController::updateView()
{
  mMainView->updateView();
}
void ViewController::updateModel(common::RegisterType regType, model::dataPair &registerWithValue)
{
  switch (regType) {
  case common::RegisterType::Coils: mModbusModel->setCoilAddress(registerWithValue);
  case common::RegisterType::HoldingRegister: mModbusModel->setHoldingRegisterAddress(registerWithValue);
  case common::RegisterType::InputRegister: mModbusModel->setInputRegisterAddress(registerWithValue);
  case common::RegisterType::InputStatus: mModbusModel->setInputStatusAddress(registerWithValue);
  }
}
}  // namespace controllers