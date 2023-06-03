
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../data-sources/csv/csv.h"
#include "../data-sources/expressions/rename/rename.h"

using namespace std;

void testRename(){
  CSVDataSource csvDataSource("src/test/assets/test10.csv");
  vector<string> newHeader;
  newHeader.push_back("vek");
  newHeader.push_back(csvDataSource.getHeader()[1]);
  newHeader.push_back("vyska");
  HeaderValueContainer headerValueContainer(newHeader, csvDataSource.getHeader());
  RenameExpression renameExpression(&csvDataSource, headerValueContainer);
  assert(renameExpression.getHeaderSize() == 3);
  assert(renameExpression.getHeader()[0] == "vek");
  assert(renameExpression.getHeader()[1] == "age");
  assert(renameExpression.getHeader()[2] == "vyska");
}

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

int main() {
  testCsvDataSource();
  return 0;
}
