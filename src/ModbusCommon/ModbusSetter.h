#pragma once
#include "Configuration.h"

namespace modbusThread {
bool setModbus(const configuration::Configuration &modbusConf, int address, int value);

bool setCoilModbus(const configuration::Configuration &modbusConf, uint16_t address, bool value);
}  // namespace Modbus
