#pragma once

#include <string>
#include <utility>

#include "Configuration.h"
#include "RegisterType.h"
#include "ViewController.h"
#include "../ModbusCommon/modbus.h"

namespace modbusThread {
class FillModel
{
  using dataPair = std::pair<unsigned int, std::string>;
public:
  FillModel(const std::shared_ptr<controllers::ViewController> &mViewController, modbus &mModbusConnection);

  void fillCoilsModel(unsigned int start, unsigned int stop);

  void fillInputStatusModel(unsigned int start, unsigned int stop);

  void FillInputRegisterModel(unsigned int start, unsigned int stop);

  void FillHoldingRegisterModel(unsigned int start, unsigned int stop);

private:
  std::shared_ptr<controllers::ViewController> mViewController;
  modbus& mModbusConnection;
};
}
