#pragma once
#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <type_traits>
#include <functional>

#include "Configuration.h"
#include "RegisterType.h"
#include "ViewController.h"
#include "modbus.h"

namespace Modbus {
class ModbusDaemon
{
  using dataPair = std::pair<unsigned int, std::string>;

public:
  ModbusDaemon(const std::shared_ptr<controllers::ViewController> &mViewController, const configuration::Configuration &mConfiguration);

  virtual ~ModbusDaemon();

  void run();

  void stopThread();

private:
  void runFunction();

  void fillModelCoils(unsigned int start, unsigned int stop, modbus &modbusConnection);

  void fillIntegerModel(common::RegisterType type, unsigned int start, unsigned int stop, modbus &modbusConnection);

  std::shared_ptr<controllers::ViewController> mViewController;
  configuration::Configuration mConfiguration;
  std::thread mThread;
  std::atomic_bool mRun;
  std::mutex mMutex;
};
}  // namespace Modbus
