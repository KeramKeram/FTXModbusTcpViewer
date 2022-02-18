#include "loadJsonConfiguration.h"

namespace io {

loadJsonConfiguration::loadJsonConfiguration(const std::string &filePath)
{
  std::ifstream file(filePath);
  if (file.is_open()) {
    file >> mValue;
  }
}

RegisterConfiguration loadJsonConfiguration::getRegisterConfiguration()
{
  RegisterConfiguration configuration;
  configuration.mCoilsStart = mValue["register-interval"]["coils-start"].asUInt();
  configuration.mCoilsEnd = mValue["register-interval"]["coils-end"].asUInt();
  configuration.mInputStatusStart = mValue["register-interval"]["input-status-start"].asUInt();
  configuration.mInputStatusEnd = mValue["register-interval"]["input-status-end"].asUInt();
  configuration.mInputRegistersStart = mValue["register-interval"]["input-register-start"].asUInt();
  configuration.mInputRegistersEnd = mValue["register-interval"]["input-register-end"].asUInt();
  configuration.mHoldingRegistersStart = mValue["register-interval"]["holding-register-start"].asUInt();
  configuration.mHoldingRegistersEnd = mValue["register-interval"]["holding-register-end"].asUInt();
  return configuration;
}

}