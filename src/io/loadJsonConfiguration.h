#pragma once
#include "json/json.h"

#include <fstream>
#include <string>

namespace io {
struct RegisterConfiguration
{
  unsigned int mCoilsStart{ 0 };
  unsigned int mCoilsEnd{ 0 };
  unsigned int mInputStatusStart{ 0 };
  unsigned int mInputStatusEnd{ 0 };
  unsigned int mInputRegistersStart{ 0 };
  unsigned int mInputRegistersEnd{ 0 };
  unsigned int mHoldingRegistersStart{ 0 };
  unsigned int mHoldingRegistersEnd{ 0 };
};

class loadJsonConfiguration
{
public:
  loadJsonConfiguration(const std::string &filePath);

  ~loadJsonConfiguration() = default;

  RegisterConfiguration getRegisterConfiguration();

private:
  Json::Value mValue;
};
}  // namespace io