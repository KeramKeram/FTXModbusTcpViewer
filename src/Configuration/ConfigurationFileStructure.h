#pragma once

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
}  // namespace configuration