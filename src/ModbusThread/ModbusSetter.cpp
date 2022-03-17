#include "ModbusSetter.h"

#include "../ModbusCommon/modbus.h"

namespace modbusThread {
bool setHoldingModbus(const configuration::Configuration &modbusConf, uint16_t address, uint16_t value)
{
  auto modbusConnection = modbus(modbusConf.mNetworkConfiguration.mModbusTcpAddress, modbusConf.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(modbusConf.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_register(address, value) != 0) { return false; }
  return true;
}

bool setCoilModbus(const configuration::Configuration &modbusConf, uint16_t address, bool value)
{
  auto modbusConnection = modbus(modbusConf.mNetworkConfiguration.mModbusTcpAddress, modbusConf.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(modbusConf.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_coil(address, value) != 0) { return false; }
  return true;
}
}  // namespace Modbus