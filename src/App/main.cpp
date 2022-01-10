#include <memory>

#include "MainView.h"
#include "ModbusModel.h"
#include "ViewController.h"

int main()
{
    auto mainView = std::make_shared<views::MainView>();
    auto modbusModel = std::make_shared<model::ModbusModel>();
    auto viewController = std::make_unique<controllers::ViewController>(modbusModel, mainView);

    viewController->showView();
}