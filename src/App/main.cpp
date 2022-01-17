#include <memory>

#include "MainView.h"
#include "ModbusModel.h"
#include "ViewController.h"

int main()
{
    auto mainView = std::make_shared<views::MainView>();
    auto empty_lambda = []() {};
    auto modbusModel = std::make_shared<model::ModbusModel>(empty_lambda);
    auto viewController = std::make_unique<controllers::ViewController>(modbusModel, mainView);

    viewController->showView();
}