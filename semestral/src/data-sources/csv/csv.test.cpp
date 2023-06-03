#include "./csv.h"

using namespace std;

void testCsvDataSource() {
  try {
    CSVDataSource csvDataSource("src/test/assets/non-existent.csv");
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
  CSVDataSource csvDataSource("src/test/assets/test.csv");
  assert(csvDataSource.hasNextRow() == true);
  vector<string> header = csvDataSource.getHeader();
  assert(header.size() == 3);
  assert(header[0] == "name");
  assert(header[1] == "age");
  assert(header[2] == "height");
  assert(csvDataSource.getHeaderSize() == 3);
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