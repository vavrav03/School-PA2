#include "../data-sources/file/csv.h"
#include <iostream>
#include <cassert>
#include "../utils/utils.h"

using namespace std;

void testCsvDataSource() {
  cout << "- RUNNING: testCsvDataSource" << endl;
  try {
    CSVDataSource csvDataSource("src/test/assets/non-existent.csv", "nonexistent");
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
  CSVDataSource csvDataSource("src/test/assets/test.csv", "test");
  assert(csvDataSource.getHeaderSize() == 3);
  assert(csvDataSource.getHeaderName(0) == "name");
  assert(csvDataSource.getHeaderName(1) == "age");
  assert(csvDataSource.getHeaderName(2) == "height");
  assert(equalsVectors(csvDataSource.getNextRow(), vector<string>{"John", "25", "180"}));
  assert(csvDataSource.getNextRow().empty());
  csvDataSource.reset();
  csvDataSource.reset();
  csvDataSource.reset();
  assert(equalsVectors(csvDataSource.getNextRow(), vector<string>{"John", "25", "180"}));
  assert(csvDataSource.getNextRow().empty());
}