#pragma once
#include <functional>
#include <memory>

#include "SafeTHMap.h"

namespace model {
    using safeMap = containers::SafeTHMap<std::string, std::string>;
    class ModbusModel {
    public:
        ModbusModel(std::function<void()> update);
        ~ModbusModel() = default;

    private:
        std::shared_ptr<safeMap> mCoils;
        std::shared_ptr<safeMap> mInputStatus;
        std::shared_ptr<safeMap> mInputRegisters;
        std::shared_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
