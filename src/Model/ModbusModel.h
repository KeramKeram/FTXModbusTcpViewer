#pragma once
#include <functional>
#include <memory>

#include "SafeTHMap.h"

namespace model {
    using safeMap = containers::SafeTHMap<std::string, std::string>;
    using dataPair = std::pair<std::string, std::string>;

    class ModbusModel {
    public:
        ModbusModel(std::function<void()> update);
        ~ModbusModel() = default;

        void setUpdateCallback(std::function<void()> modelsUpdatedCallback);

        const std::shared_ptr<safeMap> &getMCoils() const;

        const std::shared_ptr<safeMap> &getMInputStatus() const;

        const std::shared_ptr<safeMap> &getMInputRegisters() const;

        const std::shared_ptr<safeMap> &getMHoldingRegisters() const;

        void setCoilAddress(dataPair data);

        void setInputStatusAddress(dataPair data);

        void setInputRegisterAddress(dataPair data);

        void setHoldingRegisterAddress(dataPair data);

        dataPair getCoilAddress(std::string& address);

        dataPair getInputStatusAddress(std::string& address);

        dataPair getInputRegisterAddress(std::string& address);

        dataPair getHoldingRegisterAddress(std::string& address);

    private:
        std::shared_ptr<safeMap> mCoils;
        std::shared_ptr<safeMap> mInputStatus;
        std::shared_ptr<safeMap> mInputRegisters;
        std::shared_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
