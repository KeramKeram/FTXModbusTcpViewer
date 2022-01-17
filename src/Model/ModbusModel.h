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

        void setUpdateCallback(std::function<void()> modelsUpdatedCallback);

        const std::shared_ptr<safeMap> &getMCoils() const;

        const std::shared_ptr<safeMap> &getMInputStatus() const;

        const std::shared_ptr<safeMap> &getMInputRegisters() const;

        const std::shared_ptr<safeMap> &getMHoldingRegisters() const;

    private:
        std::shared_ptr<safeMap> mCoils;
        std::shared_ptr<safeMap> mInputStatus;
        std::shared_ptr<safeMap> mInputRegisters;
        std::shared_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
