#include <memory>

#include "Configuration.h"
#include "MainView.h"
#include "ModbusModel.h"
#include "ModbusDaemon.h"
#include "ViewController.h"
#include "loadJsonConfiguration.h"
#include "ModbusSetter.h"
#include "ViewCallbacks.h"

int main()
{
  io::loadJsonConfiguration conf("configuration.json");
  configuration::Configuration configuration;
  configuration.mRegisterConfiguration = conf.getRegisterConfiguration();
  configuration.mNetworkConfiguration  = conf.getNetworkConfiguration();
  configuration.mViewConfiguration     = conf.getViewConfiguration();
  common::ControllerCallbacks controllerCallbacks;
  auto modbusWriter   = std::make_shared<modbusCommon::ModbusWriter>(configuration);
  auto modbusModel    = std::make_shared<model::ModbusModel>([]() {});
  auto mainView       = std::make_shared<views::MainView>(modbusModel, controllerCallbacks, configuration.mViewConfiguration);
  auto viewController = std::make_shared<controllers::ViewController>(modbusModel, mainView, modbusWriter, controllerCallbacks);
  auto modbusDaemon   = std::make_unique<modbusThread::ModbusDaemon>(viewController, configuration);
  modbusDaemon->run();
  viewController->showView();
}
