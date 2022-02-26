//
// Created by KeramKeram on 05.12.2021.
//

#pragma once
#include <functional>
#include <string>

namespace views {
class IView
{
public:
  virtual ~IView() = default;

  virtual void show() = 0;

  virtual void updateView() = 0;

  virtual void setSelectedModel(std::function<void(int)> func) = 0;
};
}  // namespace views