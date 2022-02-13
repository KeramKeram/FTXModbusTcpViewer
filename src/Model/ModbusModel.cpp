#include "ModbusModel.h"

namespace model {

ModbusModel::ModbusModel(std::function<void()> update)
  : mModelsUpdatedCallback(update)
  , mCoils(std::make_unique<safeMap>())
  , mInputStatus(std::make_unique<safeMap>())
  , mInputRegisters(std::make_unique<safeMap>())
  , mHoldingRegisters(std::make_unique<safeMap>())
{
}

void ModbusModel::setUpdateCallback(std::function<void()> modelsUpdatedCallback)
{
  mModelsUpdatedCallback = std::move(modelsUpdatedCallback);
}

void ModbusModel::setCoilAddress(dataPair data)
{
  mCoils->add(data.first, data.second);
  mModelsUpdatedCallback();
}

void ModbusModel::setInputStatusAddress(dataPair data)
{
  mInputStatus->add(data.first, data.second);
  mModelsUpdatedCallback();
}

void ModbusModel::setInputRegisterAddress(dataPair data)
{
  mInputRegisters->add(data.first, data.second);
  mModelsUpdatedCallback();
}

void ModbusModel::setHoldingRegisterAddress(dataPair data)
{
  mHoldingRegisters->add(data.first, data.second);
  mModelsUpdatedCallback();
}

dataPair ModbusModel::getCoilAddress(unsigned int address)
{
  return model::dataPair(address, mCoils->get(address));
}

dataPair ModbusModel::getInputStatusAddress(unsigned int address)
{
  return { model::dataPair(address, mInputStatus->get(address)) };
}

dataPair ModbusModel::getInputRegisterAddress(unsigned int address)
{
  return { model::dataPair(address, mInputRegisters->get(address)) };
}

dataPair ModbusModel::getHoldingRegisterAddress(unsigned int address)
{
  return { model::dataPair(address, mHoldingRegisters->get(address)) };
}
std::vector<std::string> ModbusModel::getAllValuesForCoils()
{
  return mCoils->getAllValues();
}
std::vector<std::string> ModbusModel::getAllValuesForInputStatus()
{
  return mInputStatus->getAllValues();
}
std::vector<std::string> ModbusModel::getAllValuesForInputRegisters()
{
  return mInputRegisters->getAllValues();
}
std::vector<std::string> ModbusModel::getAllValuesForHoldingRegisters()
{
  return mHoldingRegisters->getAllValues();
}

}  // namespace model