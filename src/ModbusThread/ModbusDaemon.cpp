#include "ModbusDaemon.h"

#include "Configuration.h"
#include "FillModel.h"
#include "../ModbusCommon/modbus.h"

namespace modbusThread {

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
  auto status = modbusConnection.modbus_connect();
  if (!status) {
    return;
  }
  int selectedModelInView = 0;
  FillModel modelFiller(mViewController, modbusConnection);
  while (mRun.load()) {
    selectedModelInView = mViewController->getCurrentModelView();

    switch (selectedModelInView) {
    case 0: modelFiller.fillCoilsModel(mConfiguration.mRegisterConfiguration.mCoilsStart, mConfiguration.mRegisterConfiguration.mCoilsEnd); break;
    case 1:
      modelFiller.fillInputStatusModel(mConfiguration.mRegisterConfiguration.mInputStatusStart,
                                       mConfiguration.mRegisterConfiguration.mInputStatusEnd);
      break;
    case 2:
      modelFiller.FillInputRegisterModel(mConfiguration.mRegisterConfiguration.mInputRegistersStart,
                                         mConfiguration.mRegisterConfiguration.mInputRegistersEnd);
      break;
    case 3:
      modelFiller.FillHoldingRegisterModel(mConfiguration.mRegisterConfiguration.mHoldingRegistersStart,
                                           mConfiguration.mRegisterConfiguration.mHoldingRegistersEnd);
      break;
    }
    /* It's better to update view from here than update it on every change in model */
    mViewController->updateView();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.25s);
  }
}

}  // namespace Modbus