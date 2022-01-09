#include "ModbusModel.h"
namespace model {

    ModbusModel::ModbusModel() {
        mCoils = std::make_unique<safeMap>();
        mInputStatus = std::make_unique<safeMap>();
        mInputRegisters = std::make_unique<safeMap>();
        mHoldingRegisters = std::make_unique<safeMap>();
    }
}// namespace model