#pragma once

#include <fstream>
#include <string>

#include "ConfigurationFileStructure.h"

#include "json/json.h"

namespace io {
constexpr char REGISTER_INTERVAL[]  = "register-interval";
constexpr char NETWORK_CONFIGURATION[]  = "network-configuration";

class loadJsonConfiguration
{
public:
  loadJsonConfiguration(const std::string &filePath);

  ~loadJsonConfiguration() = default;

  configuration::RegisterConfiguration getRegisterConfiguration();

  configuration::NetworkConfiguration getNetworkConfiguration();

private:
  Json::Value mValue;
};
}  // namespace io