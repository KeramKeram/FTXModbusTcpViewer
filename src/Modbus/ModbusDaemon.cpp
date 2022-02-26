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

  while (mRun.load()) {
    fillModelCoils(mConfiguration.mRegisterConfiguration.mCoilsStart, mConfiguration.mRegisterConfiguration.mCoilsEnd, modbusConnection);
    fillIntegerModel(common::RegisterType::InputRegister,
                     mConfiguration.mRegisterConfiguration.mInputRegistersStart,
                     mConfiguration.mRegisterConfiguration.mInputRegistersEnd,
                     modbusConnection);
    fillIntegerModel(common::RegisterType::HoldingRegister,
                     mConfiguration.mRegisterConfiguration.mHoldingRegistersStart,
                     mConfiguration.mRegisterConfiguration.mHoldingRegistersEnd,
                     modbusConnection);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.1s);
  }
}

void ModbusDaemon::fillModelCoils(unsigned int start, unsigned int stop, modbus &modbusConnection)
{
  bool readReg = false;
  for (unsigned int i = start; i < stop; i++) {
    modbusConnection.modbus_read_coils(i, 1, &readReg);
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(common::RegisterType::Coils, reg);
  }
}

void ModbusDaemon::fillIntegerModel(common::RegisterType type, unsigned int start, unsigned int stop, modbus &modbusConnection)
{
  if (type == common::RegisterType::Coils || type == common::RegisterType::InputStatus) { return; }
  uint16_t readReg = 0;
  for (unsigned int i = start; i < stop; i++) {
    switch (type) {
    case common::RegisterType::HoldingRegister: modbusConnection.modbus_read_holding_registers(i, 1, &readReg); break;
    case common::RegisterType::InputRegister: modbusConnection.modbus_read_input_registers(i, 1, &readReg); break;
    }
    dataPair reg(i, std::to_string(readReg));
    mViewController->updateModel(type, reg);
  }
}

}  // namespace Modbus