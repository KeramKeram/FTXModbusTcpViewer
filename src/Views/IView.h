#pragma once
#include <string>

namespace views {
class IView
{
public:
  virtual ~IView() = default;

  virtual void show() = 0;

  virtual void updateView() = 0;

  virtual void showConnectionError(std::string error) = 0;
};
}  // namespace views