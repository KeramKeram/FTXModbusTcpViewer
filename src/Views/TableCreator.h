#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

namespace views {
using namespace ftxui;
constexpr int VIEW_COLUMNS    = 2;
constexpr int VIEW_ROWS       = 10;
constexpr int VIEW_BOX_WIDTH  = 8;
constexpr int VIEW_BOX_HEIGHT = 3;

class TableCreator
{
public:
  std::vector<ftxui::Elements> createTable(std::vector<std::string> &vals);

private:
  struct BoxParameter
  {
    BoxParameter(std::string mBoxValue, uint8_t mHue, uint8_t mSaturation, uint8_t mHsvValue)
      : mBoxValue(std::move(mBoxValue)), mHue(mHue), mSaturation(mSaturation), mHSVValue(mHsvValue){};
    ~BoxParameter() = default;
    std::string mBoxValue;
    uint8_t mHue;
    uint8_t mSaturation;
    uint8_t mHSVValue;
  };

  static TableCreator::BoxParameter createBoxParameters(std::string value, int hue, int hsv);
  static ftxui::Element makeBox(const BoxParameter &param);
  static std::vector<Element> createFirstRow(int partsInRow);
  static void populateTable(const std::vector<std::string> &vals, std::vector<Elements> &rows, int partsInRow);
};

}  // namespace views
