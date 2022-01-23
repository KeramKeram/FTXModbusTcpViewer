#include <memory>

#include "MainView.h"
#include "ModbusModel.h"
#include "ModbusDaemon.h"
#include "ViewController.h"

int main() {
    auto modbusModel = std::make_shared<model::ModbusModel>([]() {});
    auto mainView = std::make_shared<views::MainView>(modbusModel);
    auto viewController = std::make_unique<controllers::ViewController>(modbusModel, mainView);
    auto modbusDaemon = std::make_unique<modbus::ModbusDaemon>(modbusModel);
    modbusDaemon->run();
    viewController->showView();
}