#pragma once
#include <memory>
#include <thread>
#include <atomic>
#include <queue>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "ModbusModel.h"

namespace modbus {
class ModbusDaemon
{
public:
  ModbusDaemon(const std::shared_ptr<model::ModbusModel> &modbusModel);
  virtual ~ModbusDaemon();
  void run();

  void stopThread();

private:
  void runFunction();

  std::shared_ptr<model::ModbusModel> mModbusModel;
  std::thread mThread;
  std::atomic_bool mRun;
  std::mutex mMutex;
};
}  // namespace modbus
