#pragma once
#include <functional>

namespace common {
  struct ControllerCallbacks {
    std::function<void(int)> mUpdateSelectedModel;
    std::function<void(uint16_t, uint16_t)> mSetHoldingRegister;
    std::function<void(uint16_t, bool)> mSetCoilRegister;
  };
};