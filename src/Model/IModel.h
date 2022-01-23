#pragma once

#include <functional>

namespace model {
    class IModel {
    public:
        IModel() = default;
        virtual ~IModel() = default;

        virtual void setUpdateCallback(std::function<void()> modelsUpdatedCallback) = 0;
    };
}// namespace model