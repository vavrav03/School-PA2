
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./data-sources/csv/csv.h"
#include "./data-types/string/string-type.h"

using namespace std;

void testCsvDataSource() {
  // create CSV file with header: "name", "age", "height"
  std::ofstream csvFile;
  csvFile.open("test.csv");
  csvFile << "name,age,height\n";
  csvFile << "John,25,180\n";
  csvFile.close();

  CSVDataSource csvDataSource("test.csv");
  assert(csvDataSource.hasNextRow() == true);
  vector<string> header = csvDataSource.getHeader();
  assert(header.size() == 3);
  assert(header[0] == "name");
  assert(header[1] == "age");
  assert(header[2] == "height");
  assert(csvDataSource.getHeaderSize() == 3);
  assert(csvDataSource.hasNextRow() == true);
  DataRow row = csvDataSource.getNextRow();
  assert(*(row[0]) == StringType("John"));
  assert(*(row[1]) == StringType("25"));
  assert(*(row[2]) == StringType("180"));
}

int main() {
  testCsvDataSource();
  return 0;
}
