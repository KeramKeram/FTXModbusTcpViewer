#include <memory>

#include "MainView.h"
#include "ModbusModel.h"
#include "ModbusDaemon.h"
#include "ViewController.h"

int main() {
    auto mainView = std::make_shared<views::MainView>();
    auto modbusModel = std::make_shared<model::ModbusModel>([]() {});
    auto viewController = std::make_unique<controllers::ViewController>(modbusModel, mainView);
    auto modbusDaemon = std::make_unique<modbus::ModbusDaemon>(modbusModel);
    modbusDaemon->run();
    viewController->showView();
}