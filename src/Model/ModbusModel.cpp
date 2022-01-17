#include "ModbusModel.h"

namespace model {

    ModbusModel::ModbusModel(std::function<void()> update) : mModelsUpdatedCallback(update) {
        mCoils = std::shared_ptr<safeMap>();
        mInputStatus = std::shared_ptr<safeMap>();
        mInputRegisters = std::shared_ptr<safeMap>();
        mHoldingRegisters = std::shared_ptr<safeMap>();
    }
    void ModbusModel::setUpdateCallback(std::function<void()> modelsUpdatedCallback) {
        mModelsUpdatedCallback = modelsUpdatedCallback;
    }

    const std::shared_ptr<safeMap> &ModbusModel::getMCoils() const { return mCoils; }

    const std::shared_ptr<safeMap> &ModbusModel::getMInputStatus() const { return mInputStatus; }

    const std::shared_ptr<safeMap> &ModbusModel::getMInputRegisters() const { return mInputRegisters; }

    const std::shared_ptr<safeMap> &ModbusModel::getMHoldingRegisters() const { return mHoldingRegisters; }

    void ModbusModel::setCoilAddress(dataPair data) {}

    void ModbusModel::setInputStatusAddress(dataPair data) {}

    void ModbusModel::setInputRegisterAddress(dataPair data) {}

    void ModbusModel::setHoldingRegisterAddress(dataPair data) {}

    dataPair ModbusModel::getCoilAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getInputStatusAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getInputRegisterAddress(unsigned int address) { return model::dataPair(); }

    dataPair ModbusModel::getHoldingRegisterAddress(unsigned intaddress) { return model::dataPair(); }

}// namespace model