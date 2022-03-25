#include "TableCreator.h"

#include <string>
#include <utility>
#include <vector>

namespace views {
using namespace ftxui;

TableCreator::TableCreator(configuration::ViewConfiguration &viewConfiguration) : mViewConfiguration(viewConfiguration)
{
}

std::vector<Elements> views::TableCreator::createTable(std::vector<std::string> &vals)
{
  std::vector<Elements> rows;
  int partsInRow = static_cast<int>(vals.size() / mViewConfiguration.mRowsNumber) + 1;
  if (vals.size() % 10 != 0) { ++partsInRow; }
  auto firstRow = createFirstRow(partsInRow);
  rows.push_back(firstRow);
  populateTable(vals, rows, partsInRow);
  return rows;
}

void views::TableCreator::populateTable(const std::vector<std::string> &vals, std::vector<Elements> &rows, int partsInRow)
{
  size_t counter = 0;
  for (unsigned int x = 0; x < mViewConfiguration.mRowsNumber; ++x) {
    rows.push_back(createRow(vals, partsInRow, counter));
  }
}

std::vector<Element> views::TableCreator::createRow(const std::vector<std::string> &vals, int partsInRow, size_t &counter)
{
  std::string value;
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
  return row;
}

std::vector<Element> views::TableCreator::createFirstRow(int partsInRow)
{
  std::vector<Element> firstRow;
  std::string numbers;
  for (int i = 0; i < partsInRow; i++) {
    numbers = columnDescription(i);
    firstRow.push_back(makeBox(createBoxParameters(numbers, 185, 100)));
  }
  return firstRow;
}

std::string views::TableCreator::columnDescription(int i)
{
  std::string number;
  if (i != 0) {
    number = std::to_string(i-1);

  } else {
    number = "-";
  }
    return number;
}

TableCreator::BoxParameter TableCreator::createBoxParameters(std::string value, int hue, int hsv)
{
  TableCreator::BoxParameter param(std::move(value), hue, 255, hsv);
  return param;
}

Element TableCreator::makeBox(const TableCreator::BoxParameter &param)
{
  const auto [value, hue, saturation, hvValue] = param;
  return text(value) | center | size(WIDTH, EQUAL, VIEW_BOX_WIDTH) | size(HEIGHT, EQUAL, VIEW_BOX_HEIGHT) | border
         | bgcolor(Color::HSV(hue, saturation, hvValue));
}
}  // namespace views