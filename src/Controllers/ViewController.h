#pragma once

#include <memory>

#include "MainView.h"
#include "ModbusModel.h"

namespace controllers {

    class ViewController {
    public:
        ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel,
                       const std::shared_ptr<views::IView> &mMainView);

        virtual ~ViewController() = default;

        void showView();

    private:
        std::shared_ptr<model::ModbusModel> mModbusModel;
        std::shared_ptr<views::IView> mMainView;
    };
}// namespace controllers
