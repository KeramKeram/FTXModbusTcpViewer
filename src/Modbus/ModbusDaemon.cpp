#include "ModbusDaemon.h"

namespace modbus {

    ModbusDaemon::ModbusDaemon(const std::shared_ptr<model::ModbusModel> &mModbusModel) : mModbusModel(mModbusModel) {}

    void ModbusDaemon::run() {
        mThread = std::thread(&ModbusDaemon::runFunction, this);
    }
    void ModbusDaemon::stopThread() {
        mRun.store(false);
        if (mThread.joinable()){
            mThread.join();
        }
    }

    void ModbusDaemon::runFunction() {
        mRun.store(true);
        while (mRun.load()) {

        }
    }
}