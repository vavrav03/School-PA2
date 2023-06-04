#include "./csv.h"
#include <iostream>

using namespace std;

void testCsvDataSource() {
  cout << "- RUNNING: testCsvDataSource" << endl;
  try {
    CSVDataSource csvDataSource("src/test/assets/non-existent.csv");
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
  CSVDataSource csvDataSource("src/test/assets/test.csv");
  assert(csvDataSource.hasNextRow() == true);
  assert(csvDataSource.getHeaderSize() == 3);
  assert(csvDataSource.getHeaderName(0) == "name");
  assert(csvDataSource.getHeaderName(1) == "age");
  assert(csvDataSource.getHeaderName(2) == "height");
  assert(csvDataSource.hasNextRow() == true);
  vector<string> row = csvDataSource.getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");
  assert(csvDataSource.hasNextRow() == false);
  try {
    csvDataSource.getNextRow();
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
}