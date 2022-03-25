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
  /* This function return "X" if result of reading modbus reg. is bad. In other case we have value converted to string. */
  template<typename T>
  std::string convertToStringValueBasedOnResult(T value, int result) {
    std::string output;
    if (result == 0) {
      output = std::to_string(value);
    } else {
      output = "X";
    }
    return output;
  }


  std::shared_ptr<controllers::ViewController> mViewController;
  modbus& mModbusConnection;
};
}
