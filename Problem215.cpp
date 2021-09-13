#include <iostream>
#include <vector>

typedef std::vector<unsigned char> Row;
std::vector<Row> allRows;

std::vector<std::vector<unsigned int>> compatible;

void generateRows(Row row, unsigned char maxWidth)
{
  auto width = row.empty() ? 0 : row.back();

  if (width + 2 == maxWidth || width + 3 == maxWidth)
  {
    allRows.push_back(row);
    return;
  }

  if (width + 1 == maxWidth)
    return;

  row.push_back(width + 2);
  generateRows(row, maxWidth);

  row.back()++; 
  generateRows(row, maxWidth);
}

void checkCompatibility()
{
  compatible.resize(allRows.size());

  for (size_t i = 0; i < allRows.size(); i++)
    for (size_t j = i + 1; j < allRows.size(); j++)
    {
      bool valid = true;

      auto current1 = allRows[i].begin();
      auto current2 = allRows[j].begin();
      while (current1 != allRows[i].end() && current2 != allRows[j].end())
      {
        if (*current1 < *current2)
          current1++;
        else
          if (*current2 < *current1)
            current2++;
        else
        {
          valid = false;
          break;
        }
      }

      if (valid)
      {
        compatible[i].push_back(j);
        compatible[j].push_back(i);
      }
    }
}

unsigned long long count(unsigned int rowId, unsigned int rowsLeft)
{
  if (rowsLeft == 1)
    return 1;

  static std::vector<std::vector<unsigned long long>> cache(allRows.size());
  const unsigned long long Invalid = 0;
  if (cache[rowId].size() <= rowsLeft)
    cache[rowId].resize(rowsLeft + 1, Invalid); 
  else
    if (cache[rowId][rowsLeft] != Invalid)
      return cache[rowId][rowsLeft];

  unsigned long long result = 0;
  for (auto x : compatible[rowId])
    result += count(x, rowsLeft - 1);

  cache[rowId][rowsLeft] = result;
  return result;
}

int main()
{
  unsigned int width  = 32;
  unsigned int height = 10;
  std::cin >> width >> height;

  Row empty;
  generateRows(empty, width);

  checkCompatibility();

  unsigned long long result = 0;
  for (unsigned int i = 0; i < allRows.size(); i++)
    result += count(i, height);

  std::cout << result << std::endl;
  return 0;
