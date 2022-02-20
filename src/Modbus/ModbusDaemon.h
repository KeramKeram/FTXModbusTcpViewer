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

#include "ViewController.h"

namespace Modbus {
class ModbusDaemon
{
public:
  explicit ModbusDaemon(const std::shared_ptr<controllers::ViewController> &mViewController);
  virtual ~ModbusDaemon();
  void run();

  void stopThread();

private:
  void runFunction();

  std::shared_ptr<controllers::ViewController> mViewController;
  std::thread mThread;
  std::atomic_bool mRun;
  std::mutex mMutex;
};
}  // namespace Modbus
