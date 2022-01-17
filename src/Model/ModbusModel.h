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

        void setCoilAddress(dataPair data);

        void setInputStatusAddress(dataPair data);

        void setInputRegisterAddress(dataPair data);

        void setHoldingRegisterAddress(dataPair data);

        dataPair getCoilAddress(unsigned int address);

        dataPair getInputStatusAddress(unsigned int address);

        dataPair getInputRegisterAddress(unsigned int address);

        dataPair getHoldingRegisterAddress(unsigned int address);

    private:
        std::unique_ptr<safeMap> mCoils;
        std::unique_ptr<safeMap> mInputStatus;
        std::unique_ptr<safeMap> mInputRegisters;
        std::unique_ptr<safeMap> mHoldingRegisters;

        std::function<void()> mModelsUpdatedCallback;
    };
}// namespace model
