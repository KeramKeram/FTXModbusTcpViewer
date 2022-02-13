#pragma once
#include <functional>
#include <memory>

#include "IModel.h"
#include "SafeTHMap.h"

namespace model {
using safeMap  = containers::SafeTHMap<unsigned int, std::string>;
using dataPair = std::pair<unsigned int, std::string>;

class ModbusModel : public IModel
{
public:
  explicit ModbusModel(std::function<void()> update);

  ~ModbusModel() override = default;

  void setUpdateCallback(std::function<void()> modelsUpdatedCallback) override;

  void setCoilAddress(dataPair data);

  void setInputStatusAddress(dataPair data);

  void setInputRegisterAddress(dataPair data);

  void setHoldingRegisterAddress(dataPair data);

  dataPair getCoilAddress(unsigned int address);

  dataPair getInputStatusAddress(unsigned int address);

  dataPair getInputRegisterAddress(unsigned int address);

  dataPair getHoldingRegisterAddress(unsigned int address);

  std::vector<std::string> getAllValuesForCoils();

  std::vector<std::string> getAllValuesForInputStatus();

  std::vector<std::string> getAllValuesForInputRegisters();

  std::vector<std::string> getAllValuesForHoldingRegisters();

private:
  std::unique_ptr<safeMap> mCoils;
  std::unique_ptr<safeMap> mInputStatus;
  std::unique_ptr<safeMap> mInputRegisters;
  std::unique_ptr<safeMap> mHoldingRegisters;

  std::function<void()> mModelsUpdatedCallback;
};
}  // namespace model
