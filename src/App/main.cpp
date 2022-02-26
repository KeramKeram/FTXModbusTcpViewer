#include <memory>

#include "Configuration.h"
#include "MainView.h"
#include "ModbusModel.h"
#include "ModbusDaemon.h"
#include "ViewController.h"
#include "loadJsonConfiguration.h"
int main()
{
  io::loadJsonConfiguration conf("wrong_path");
  configuration::Configuration configuration;
  configuration.mRegisterConfiguration = conf.getRegisterConfiguration();
  configuration.mNetworkConfiguration  = conf.getNetworkConfiguration();
  auto modbusModel                     = std::make_shared<model::ModbusModel>([]() {});
  auto mainView       = std::make_shared<views::MainView>(modbusModel, [](int x){});
  auto viewController = std::make_shared<controllers::ViewController>(modbusModel, mainView);
  auto modbusDaemon   = std::make_unique<Modbus::ModbusDaemon>(viewController, configuration);
  modbusDaemon->run();
  viewController->showView();
}
