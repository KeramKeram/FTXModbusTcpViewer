#include "ModbusModel.h"

namespace model {

    ModbusModel::ModbusModel(std::function<void()> update) : mModelsUpdatedCallback(update) {
        mCoils = std::shared_ptr<safeMap>();
        mInputStatus = std::shared_ptr<safeMap>();
        mInputRegisters = std::shared_ptr<safeMap>();
        mHoldingRegisters = std::shared_ptr<safeMap>();
    }
}// namespace model