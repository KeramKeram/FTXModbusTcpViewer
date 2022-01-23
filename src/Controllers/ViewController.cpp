#include "ViewController.h"

namespace controllers {
    ViewController::ViewController(const std::shared_ptr<model::ModbusModel> &mModbusModel,
                                   const std::shared_ptr<views::IView> &mMainView)
        : mModbusModel(mModbusModel), mMainView(mMainView) {
        mModbusModel->setUpdateCallback([&mMainView]() {});
    }

    void ViewController::showView() { mMainView->show(); }

    void ViewController::updateView() {}
}// namespace controllers