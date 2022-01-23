#pragma once
#include <string>
namespace configuration {
    struct NetworkConfiguration {
        std::string mModbusTcpAddress;
        unsigned int mTCPPort;
    };

    struct ModbusConfiguration {
        NetworkConfiguration mNetworkConfiguration;
    };
}// namespace configuration