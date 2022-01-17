#include "ModbusModel.h"

namespace model {

    ModbusModel::ModbusModel(std::function<void()> update) : mModelsUpdatedCallback(update) {
        mCoils = std::make_unique<safeMap>();
        mInputStatus = std::make_unique<safeMap>();
        mInputRegisters = std::make_unique<safeMap>();
        mHoldingRegisters = std::make_unique<safeMap>();
    }
    void ModbusModel::setUpdateCallback(std::function<void()> modelsUpdatedCallback) {
        mModelsUpdatedCallback = modelsUpdatedCallback;
    }

    void ModbusModel::setCoilAddress(dataPair data) {}

    void ModbusModel::setInputStatusAddress(dataPair data) {}

    void ModbusModel::setInputRegisterAddress(dataPair data) {}

    void ModbusModel::setHoldingRegisterAddress(dataPair data) {}

    dataPair ModbusModel::getCoilAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getInputStatusAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getInputRegisterAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getHoldingRegisterAddress(unsigned intaddress) { return model::dataPair(); }

}// namespace model