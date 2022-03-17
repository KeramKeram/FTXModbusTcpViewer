#include "ModbusSetter.h"

#include "modbus.h"

namespace modbusCommon {
ModbusWriter::ModbusWriter(const configuration::Configuration &modbusConfiguration) : mModbusConfiguration(modbusConfiguration)
{
}

bool ModbusWriter::setHoldingModbus(uint16_t address, uint16_t value)
{
  auto modbusConnection = modbus(mModbusConfiguration.mNetworkConfiguration.mModbusTcpAddress, mModbusConfiguration.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(mModbusConfiguration.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_register(address, value) != 0) { return false; }
  return true;
}

bool ModbusWriter::setCoilModbus(uint16_t address, bool value)
{
  auto modbusConnection = modbus(mModbusConfiguration.mNetworkConfiguration.mModbusTcpAddress, mModbusConfiguration.mNetworkConfiguration.mTCPPort);
  modbusConnection.modbus_set_slave_id(mModbusConfiguration.mNetworkConfiguration.mSlaveId);
  auto status = modbusConnection.modbus_connect();
  if (!status || modbusConnection.modbus_write_coil(address, value) != 0) { return false; }
  return true;
}

}  // namespace modbusCommon