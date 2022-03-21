#pragma once
#include "Configuration.h"

namespace modbusCommon {
class ModbusWriter
{
public:
  explicit ModbusWriter(const configuration::Configuration &modbusConfiguration);

  bool setHoldingModbus(uint16_t address, uint16_t value);

  bool setCoilModbus(uint16_t address, bool value);

private:
  const configuration::Configuration &mModbusConfiguration;
};

}  // namespace modbusCommon
