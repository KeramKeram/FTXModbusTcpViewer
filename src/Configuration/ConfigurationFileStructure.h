#pragma once
#include <string>

namespace configuration {
struct RegisterConfiguration
{
  unsigned int mCoilsStart{ 0 };
  unsigned int mCoilsEnd{ 0 };
  unsigned int mInputStatusStart{ 0 };
  unsigned int mInputStatusEnd{ 0 };
  unsigned int mInputRegistersStart{ 0 };
  unsigned int mInputRegistersEnd{ 0 };
  unsigned int mHoldingRegistersStart{ 0 };
  unsigned int mHoldingRegistersEnd{ 0 };
};

struct NetworkConfiguration {
  std::string mModbusTcpAddress;
  unsigned int mTCPPort;
  unsigned int mSlaveId;
};

struct ViewConfiguration {
  unsigned int mRowsNumber;
};
}  // namespace configuration