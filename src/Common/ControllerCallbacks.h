#pragma once
#include <functional>

namespace common {
struct ControllerCallbacks
{
  std::function<void(int)> mUpdateSelectedModel;
  std::function<bool(uint16_t, uint16_t)> mSetHoldingRegister;
  std::function<bool(uint16_t, bool)> mSetCoilRegister;
};
};  // namespace common