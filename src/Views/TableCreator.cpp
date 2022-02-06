#include "TableCreator.h"
#include <numeric>
#include <string>
#include <thread>
#include <vector>

namespace views {
using namespace ftxui;

std::vector<Elements> views::TableCreator::createTable(std::vector<std::string> &vals)
{
  std::vector<Elements> rows;
  int partsInRow = static_cast<int>(vals.size() / 10) + 1;
  if (vals.size() % 10 != 0) { ++partsInRow; }
  auto firstRow = createFirstRow(partsInRow);
  rows.push_back(firstRow);
  populateTable(vals, rows, partsInRow);
  return rows;
}
void views::TableCreator::populateTable(const std::vector<std::string> &vals, std::vector<Elements> &rows, int partsInRow)
{
  size_t counter = 0;
  std::string value;
  for (int x = 0; x < VIEW_ROWS; ++x) {
    std::vector<Element> row;
    for (int j = 0; j < partsInRow; ++j) {
      if (counter >= vals.size()) { break; }
      if (j == 0) {
        value = "-";
        row.push_back(makeBox(createBoxParameters(value, 185, 100)));
      } else {
        value = vals[counter];
        counter++;
        row.push_back(makeBox(createBoxParameters(value, 40, 200)));
      }
    }
    rows.push_back(row);
  }
}
std::vector<Element> views::TableCreator::createFirstRow(int partsInRow)
{
  std::vector<Element> firstRow;
  for (int i = 0; i < partsInRow; i++) {
    std::string numbers = std::to_string(i);
    firstRow.push_back(makeBox(createBoxParameters(numbers, 185, 100)));
  }
  return firstRow;
}

TableCreator::BoxParameter TableCreator::createBoxParameters(std::string value, int hue, int hsv)
{
  TableCreator::BoxParameter param(value, hue, 255, hsv);
  param.mBoxValue = value;
  param.mHue      = hue;
  param.mHSVValue = hsv;
  return param;
}

Element TableCreator::makeBox(const TableCreator::BoxParameter &param)
{
  const auto [value, hue, saturation, hvValue] = param;
  return text(value) | center | size(WIDTH, EQUAL, VIEW_BOX_WIDTH) | size(HEIGHT, EQUAL, VIEW_BOX_HEIGHT) | border
         | bgcolor(Color::HSV(hue, saturation, hvValue));
}

}  // namespace views