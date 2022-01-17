#include "ModbusModel.h"

namespace model {

    ModbusModel::ModbusModel(std::function<void()> update) : mModelsUpdatedCallback(update) {
        mCoils = std::make_unique<safeMap>();
        mInputStatus = std::make_unique<safeMap>();
        mInputRegisters = std::make_unique<safeMap>();
        mHoldingRegisters = std::make_unique<safeMap>();
    }
}// namespace model