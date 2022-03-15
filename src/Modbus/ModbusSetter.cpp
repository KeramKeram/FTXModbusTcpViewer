#include "ModbusSetter.h"

#include "modbus.h"

namespace Modbus {
bool setHoldingModbus(const configuration::Configuration &modbusConf, int address, int value)
{
  auto modbusConnection = modbus(modbusConf.mNetworkConfiguration.mModbusTcpAddress, modbusConf.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(modbusConf.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_register(address, value) != 0) { return false; }
  return true;
}

bool setCoilModbus(const configuration::Configuration &modbusConf, int address, bool value)
{
  auto modbusConnection = modbus(modbusConf.mNetworkConfiguration.mModbusTcpAddress, modbusConf.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(modbusConf.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_coil(address, value) != 0) { return false; }
  return true;
}
}  // namespace Modbus