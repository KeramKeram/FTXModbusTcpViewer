#include "loadJsonConfiguration.h"

namespace io {

loadJsonConfiguration::loadJsonConfiguration(const std::string &filePath)
{
  std::ifstream file(filePath);
  if (file.is_open()) { file >> mValue; }
}

configuration::RegisterConfiguration loadJsonConfiguration::getRegisterConfiguration()
{
  configuration::RegisterConfiguration configuration;
  configuration.mCoilsStart            = mValue[REGISTER_INTERVAL]["coils-start"].asUInt();
  configuration.mCoilsEnd              = mValue[REGISTER_INTERVAL]["coils-end"].asUInt();
  configuration.mInputStatusStart      = mValue[REGISTER_INTERVAL]["input-status-start"].asUInt();
  configuration.mInputStatusEnd        = mValue[REGISTER_INTERVAL]["input-status-end"].asUInt();
  configuration.mInputRegistersStart   = mValue[REGISTER_INTERVAL]["input-register-start"].asUInt();
  configuration.mInputRegistersEnd     = mValue[REGISTER_INTERVAL]["input-register-end"].asUInt();
  configuration.mHoldingRegistersStart = mValue[REGISTER_INTERVAL]["holding-register-start"].asUInt();
  configuration.mHoldingRegistersEnd   = mValue[REGISTER_INTERVAL]["holding-register-end"].asUInt();
  return configuration;
}

configuration::NetworkConfiguration loadJsonConfiguration::getNetworkConfiguration()
{
  configuration::NetworkConfiguration netConfiguration;
  netConfiguration.mModbusTcpAddress = mValue[NETWORK_CONFIGURATION]["ip-address"].asString();
  netConfiguration.mTCPPort          = mValue[NETWORK_CONFIGURATION]["port"].asUInt();
  netConfiguration.mSlaveId          = mValue[NETWORK_CONFIGURATION]["slave-id"].asUInt();
  return netConfiguration;
}

configuration::ViewConfiguration loadJsonConfiguration::getViewConfiguration()
{
  configuration::ViewConfiguration viewConfiguration;
  viewConfiguration.mRowsNumber = mValue[VIEW_CONFIGURATION]["rows"].asUInt();
  return viewConfiguration;
}

}  // namespace io