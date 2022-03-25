#include "FillModel.h"

namespace modbusThread {

FillModel::FillModel(const std::shared_ptr<controllers::ViewController> &mViewController, modbus &mModbusConnection)
  : mViewController(mViewController), mModbusConnection(mModbusConnection)
{
}
void FillModel::fillCoilsModel(unsigned int start, unsigned int stop)
{
  bool readReg = false;
  int result = 0;
  for (unsigned int i = start; i < stop; i++) {
    result = mModbusConnection.modbus_read_coils(i, 1, &readReg);
    dataPair reg(i, convertToStringValueBasedOnResult<bool>(readReg, result));
    mViewController->updateModel(common::RegisterType::Coils, reg);
  }
}

void FillModel::fillInputStatusModel(unsigned int start, unsigned int stop)
{
  bool readReg = false;
  int result = 0;
  for (unsigned int i = start; i < stop; i++) {
    result = mModbusConnection.modbus_read_input_bits(i, 1, &readReg);
    dataPair reg(i, convertToStringValueBasedOnResult<bool>(readReg, result));
    mViewController->updateModel(common::RegisterType::InputStatus, reg);
  }
}

void FillModel::FillInputRegisterModel(unsigned int start, unsigned int stop)
{
  uint16_t readReg = 0;
  int result = 0;
  for (unsigned int i = start; i < stop; i++) {
    result = mModbusConnection.modbus_read_input_registers(i, 1, &readReg);
    dataPair reg(i, convertToStringValueBasedOnResult<uint16_t>(readReg, result));
    mViewController->updateModel(common::RegisterType::InputRegister, reg);
  }
}

void FillModel::FillHoldingRegisterModel(unsigned int start, unsigned int stop)
{
  uint16_t readReg = 0;
  int result = 0;
  for (unsigned int i = start; i < stop; i++) {
    result = mModbusConnection.modbus_read_holding_registers(i, 1, &readReg);
    dataPair reg(i, convertToStringValueBasedOnResult<uint16_t>(readReg, result));
    mViewController->updateModel(common::RegisterType::HoldingRegister, reg);
  }
}
}  // namespace Modbus