#include "FillModel.h"

namespace modbusThread {

FillModel::FillModel(const std::shared_ptr<controllers::ViewController> &mViewController, modbus &mModbusConnection)
  : mViewController(mViewController), mModbusConnection(mModbusConnection)
{
}

void FillModel::fillCoilsModel(unsigned int start, unsigned int stop)
{
  bool readReg = false;
  for (unsigned int i = start; i < stop; i++) {
    mModbusConnection.modbus_read_coils(i, 1, &readReg);
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(common::RegisterType::Coils, reg);
  }
}

void FillModel::fillInputStatusModel(unsigned int start, unsigned int stop)
{
  bool readReg = false;
  for (unsigned int i = start; i < stop; i++) {
    mModbusConnection.modbus_read_input_bits(i, 1, &readReg);
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(common::RegisterType::InputStatus, reg);
  }
}

void FillModel::FillInputRegisterModel(unsigned int start, unsigned int stop)
{
  uint16_t readReg = 0;
  for (unsigned int i = start; i < stop; i++) {
    mModbusConnection.modbus_read_input_registers(i, 1, &readReg);
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(common::RegisterType::InputRegister, reg);
  }
}

void FillModel::FillHoldingRegisterModel(unsigned int start, unsigned int stop)
{
  uint16_t readReg = 0;
  for (unsigned int i = start; i < stop; i++) {
    mModbusConnection.modbus_read_holding_registers(i, 1, &readReg);
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(common::RegisterType::HoldingRegister, reg);
  }
}
}  // namespace Modbus