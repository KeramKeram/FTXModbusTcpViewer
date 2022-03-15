#pragma once
#include "Configuration.h"

namespace Modbus {
bool setModbus(const configuration::Configuration &modbusConf, int address, int value);

bool setCoilModbus(const configuration::Configuration &modbusConf, int address, bool value);
}  // namespace Modbus
