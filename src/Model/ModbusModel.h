#pragma once
#include <functional>
#include <memory>

#include "SafeTHMap.h"

namespace model {
    using safeMap = containers::SafeTHMap<std::string, std::string>;
    struct ModbusModel {
        ModbusModel(std::function<void()> update);
        ~ModbusModel() = default;

        std::unique_ptr<safeMap> mCoils;
        std::unique_ptr<safeMap> mInputStatus;
        std::unique_ptr<safeMap> mInputRegisters;
        std::unique_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
