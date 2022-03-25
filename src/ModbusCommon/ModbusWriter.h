#pragma once
#include "Configuration.h"

namespace modbusCommon {
class ModbusWriter
{
public:
  explicit ModbusWriter(const configuration::Configuration &modbusConfiguration);

  bool setHoldingRegisterModbus(uint16_t address, uint16_t value);

  bool setCoilRegisterModbus(uint16_t address, bool value);

private:
  const configuration::Configuration &mModbusConfiguration;
};

}  // namespace modbusCommon
