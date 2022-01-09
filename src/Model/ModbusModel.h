#pragma once
#include <memory>

#include "SafeTHMap.h"

namespace model {
    using safeMap = containers::SafeTHMap<std::string, std::string>;
    struct ModbusModel {
        ModbusModel();
        ~ModbusModel() = default;

        std::unique_ptr<safeMap> mCoils;
        std::unique_ptr<safeMap> mInputStatus;
        std::unique_ptr<safeMap> mInputRegisters;
        std::unique_ptr<safeMap> mHoldingRegisters;
    };
}// namespace model
