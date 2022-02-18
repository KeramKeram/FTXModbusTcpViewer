#pragma once

#include <fstream>
#include <string>

#include "ConfigurationFileStructure.h"

#include "json/json.h"

namespace io {
constexpr char REGISTER_INTERVAL[]  = "register-interval";

class loadJsonConfiguration
{
public:
  loadJsonConfiguration(const std::string &filePath);

  ~loadJsonConfiguration() = default;

  configuration::RegisterConfiguration getRegisterConfiguration();

private:
  Json::Value mValue;
};
}  // namespace io