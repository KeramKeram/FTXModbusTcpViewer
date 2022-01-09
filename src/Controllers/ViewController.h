#pragma once

#include <memory>

#include "MainView.h"
#include "ModbusModel.h"

namespace controllers {
    class ViewController {
    private:
        model::ModbusModel mModbusModel;
        std::unique_ptr<views::IView> mMainView;
    };
}
