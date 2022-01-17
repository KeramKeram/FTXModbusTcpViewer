#pragma once
#include <functional>
#include <memory>

#include "SafeTHMap.h"

namespace model {
    using safeMap = containers::SafeTHMap<unsigned int, std::string>;
    using dataPair = std::pair<unsigned int, std::string>;

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

        dataPair getCoilAddress(unsigned int address);

        dataPair getInputStatusAddress(unsigned int address);

        dataPair getInputRegisterAddress(unsigned int address);

        dataPair getHoldingRegisterAddress(unsigned int address);

    private:
        std::shared_ptr<safeMap> mCoils;
        std::shared_ptr<safeMap> mInputStatus;
        std::shared_ptr<safeMap> mInputRegisters;
        std::shared_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
