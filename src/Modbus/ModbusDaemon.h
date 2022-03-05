#pragma once
#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <thread>
#include <type_traits>
#include <functional>

#include "Configuration.h"
#include "ViewController.h"

namespace Modbus {
class ModbusDaemon
{
public:
  ModbusDaemon(const std::shared_ptr<controllers::ViewController> &mViewController, const configuration::Configuration &mConfiguration);

  virtual ~ModbusDaemon();

  void run();

  void stopThread();

private:
  void runFunction();

  std::shared_ptr<controllers::ViewController> mViewController;
  configuration::Configuration mConfiguration;
  std::thread mThread;
  std::atomic_bool mRun;
};
}  // namespace Modbus
