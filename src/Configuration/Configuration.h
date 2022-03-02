#pragma once

#include "ConfigurationFileStructure.h"

namespace configuration {
    struct Configuration {
      RegisterConfiguration mRegisterConfiguration;
      NetworkConfiguration mNetworkConfiguration;
      ViewConfiguration mViewConfiguration;
    };
}
