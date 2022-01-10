#include "ViewController.h"

namespace controllers {
    ViewController::ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel,
                                   const std::shared_ptr<views::IView> &mMainView)
        : mModbusModel(mModbusModel), mMainView(mMainView) {}

    void ViewController::showView() {
        mMainView->show();
    }
}// namespace controllers