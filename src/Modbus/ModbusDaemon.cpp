#include "ModbusDaemon.h"

#include "Configuration.h"
#include "RegisterType.h"

namespace Modbus {

ModbusDaemon::ModbusDaemon(const std::shared_ptr<controllers::ViewController> &mViewController, const configuration::Configuration &mConfiguration)
  : mViewController(mViewController), mConfiguration(mConfiguration)
{
}


ModbusDaemon::~ModbusDaemon()
{
  stopThread();
}

void ModbusDaemon::run()
{
  mThread = std::thread(&ModbusDaemon::runFunction, this);
}

void ModbusDaemon::stopThread()
{
  mRun.store(false);
  if (mThread.joinable()) { mThread.join(); }
}

void ModbusDaemon::runFunction()
{
  mRun.store(true);
  auto modbusConnection = modbus(mConfiguration.mNetworkConfiguration.mModbusTcpAddress, mConfiguration.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(mConfiguration.mNetworkConfiguration.mSlaveId);
  modbusConnection.modbus_connect();
  int selectedModelInView = 0;
  while (mRun.load()) {
    selectedModelInView = mViewController->getCurrentModelView();

    switch (selectedModelInView) {
    case 0:
      fillBoolModel(RegisterTypeBool::Coils,
                    mConfiguration.mRegisterConfiguration.mCoilsStart,
                    mConfiguration.mRegisterConfiguration.mCoilsEnd,
                    modbusConnection);
      break;
    case 1:
      fillBoolModel(RegisterTypeBool::InputStatus,
                       mConfiguration.mRegisterConfiguration.mInputStatusStart,
                       mConfiguration.mRegisterConfiguration.mInputStatusEnd,
                       modbusConnection);
      break;
    case 2:
      fillIntegerModel(RegisterTypeInt::InputRegister,
                       mConfiguration.mRegisterConfiguration.mInputRegistersStart,
                       mConfiguration.mRegisterConfiguration.mInputRegistersEnd,
                       modbusConnection);
      break;
    case 3:
      fillIntegerModel(RegisterTypeInt::HoldingRegister,
                       mConfiguration.mRegisterConfiguration.mHoldingRegistersStart,
                       mConfiguration.mRegisterConfiguration.mHoldingRegistersEnd,
                       modbusConnection);
      break;
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.1s);
  }
}

void ModbusDaemon::fillBoolModel(RegisterTypeBool type, unsigned int start, unsigned int stop, modbus &modbusConnection)
{
  bool readReg = false;
  //TODO: Move from for loop to reding multiple regs from API.
  for (unsigned int i = start; i < stop; i++) {
    switch (type) {
    case RegisterTypeBool::Coils: modbusConnection.modbus_read_coils(i, 1, &readReg); break;
    case RegisterTypeBool::InputStatus: modbusConnection.modbus_read_input_bits(i, 1, &readReg); break;
    default: return;
    }
    dataPair reg(i, std::to_string(readReg));
    auto outputType = type == RegisterTypeBool::Coils?common::RegisterType::Coils:common::RegisterType::InputStatus;
    mViewController->updateModel(outputType, reg);
  }
}

void ModbusDaemon::fillIntegerModel(RegisterTypeInt type, unsigned int start, unsigned int stop, modbus &modbusConnection)
{
  uint16_t readReg = 0;
  //TODO: Move from for loop to reding multiple regs from API.
  for (unsigned int i = start; i < stop; i++) {
    switch (type) {
    case RegisterTypeInt::HoldingRegister: modbusConnection.modbus_read_holding_registers(i, 1, &readReg); break;
    case RegisterTypeInt::InputRegister: modbusConnection.modbus_read_input_registers(i, 1, &readReg); break;
    default: return;
    }
    dataPair reg(i, std::to_string(readReg));
    auto outputType = type == RegisterTypeInt::HoldingRegister?common::RegisterType::HoldingRegister:common::RegisterType::InputRegister;
    mViewController->updateModel(outputType, reg);
  }
}

}  // namespace Modbus