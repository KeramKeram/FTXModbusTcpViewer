#include "ModbusDaemon.h"
#include <chrono>

namespace modbus {

ModbusDaemon::ModbusDaemon(const std::shared_ptr<model::ModbusModel> &modbusModel) : mModbusModel(modbusModel)
{
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
  while (mRun.load()) {
    using dataPair = std::pair<unsigned int, std::string>;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);
    std::string str = "1";
    mModbusModel->setCoilAddress(dataPair(1, str));
  }
}
}  // namespace modbus