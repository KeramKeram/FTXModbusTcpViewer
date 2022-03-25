#include "ViewController.h"


namespace controllers {
ViewController::ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel, const std::shared_ptr<views::IView> &mMainView,
                               const std::shared_ptr<modbusCommon::ModbusWriter> &modbusWriter, common::ControllerCallbacks &callbacks)
  : mModbusModel(mModbusModel), mMainView(mMainView), mModbusWriter(modbusWriter), mSelectedModel(0)
{
  callbacks.mUpdateSelectedModel = [this](int x) { updateSelectedModel(x); };
  callbacks.mSetHoldingRegister  = [this](uint16_t adr, uint16_t val) { return setHoldingRegister(adr, val); };
  callbacks.mSetCoilRegister     = [this](uint16_t adr, bool val) { return setCoilRegister(adr, val); };
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

unsigned int ViewController::getCurrentModelView()
{
  return mSelectedModel.load();
}

void ViewController::updateSelectedModel(int selected)
{
  mSelectedModel.store(selected);
}

bool ViewController::setHoldingRegister(uint16_t address, uint16_t value)
{
  return mModbusWriter->setHoldingRegisterModbus(address, value);
}

bool ViewController::setCoilRegister(uint16_t address, bool value)
{
  return mModbusWriter->setCoilRegisterModbus(address, value);
}

void ViewController::showConnectionError(std::string error)
{
  mMainView->showConnectionError(error);
}
}  // namespace controllers