#pragma once

#include "Configuration.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

namespace views {
using namespace ftxui;
constexpr int VIEW_ROWS       = 2;
constexpr int VIEW_BOX_WIDTH  = 8;
constexpr int VIEW_BOX_HEIGHT = 3;

class TableCreator
{
public:
  explicit TableCreator(configuration::ViewConfiguration &viewConfiguration);
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
  std::vector<Element> createFirstRow(int partsInRow);
  void populateTable(const std::vector<std::string> &vals, std::vector<Elements> &rows, int partsInRow);
  static std::vector<Element> createRow(const std::vector<std::string> &vals, int partsInRow, size_t &counter) ;

  configuration::ViewConfiguration& mViewConfiguration;
  [[nodiscard]] static std::string columnDescription(int i) ;};

}  // namespace views
