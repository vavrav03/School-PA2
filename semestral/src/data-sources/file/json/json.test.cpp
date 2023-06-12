
#include "./json.h"
#include <iostream>
#include "../../../test/test_list.h"

using namespace std;

void testJSONBlockParser() {
  cout << "- RUNNING: testJSONBlockParser" << endl;
  auto block = JSONDataSource::parseBlockString("\"a\": 1, \"b\": 2");
  assert(block.first.size() == 2);
  assert(block.first[0] == "a");
  assert(block.first[1] == "b");
  assert(block.second.size() == 2);
  assert(block.second[0] == "1");

  block = JSONDataSource::parseBlockString("\"a\": 1");
  assert(block.first.size() == 1);
  assert(block.first[0] == "a");
  assert(block.second.size() == 1);

  block = JSONDataSource::parseBlockString("\"a\": 1, \n\t     \"b\":    \"2\"");
  assert(block.first.size() == 2);
  assert(block.first[0] == "a");
  assert(block.first[1] == "b");
  assert(block.second.size() == 2);
  assert(block.second[0] == "1");
  assert(block.second[1] == "2");

  try {
    block = JSONDataSource::parseBlockString("");
    assert(false);
  }
  catch (runtime_error &e) {}

  try {
    block = JSONDataSource::parseBlockString("\"a\": 1, \"b\": 2, \"c\": ");
    assert(false);
  } catch (runtime_error &e) {}

  try {
    block = JSONDataSource::parseBlockString("\"a\": 1, \"b\": , \"c\": 3\"");
    assert(false);
  } catch (runtime_error &e) {}

  try {
    block = JSONDataSource::parseBlockString("\"a\": 1, : 2, \"c\": 3");
    assert(false);
  } catch (runtime_error &e) {}

  try {
    block = JSONDataSource::parseBlockString("\"a\": 1 \"b\": 2, \"c\": 3");
    assert(false);
  } catch (runtime_error &e) {}

  try {
    block = JSONDataSource::parseBlockString("\"a\": 1, \"b\": 2, \"c\": 3,");
    assert(false);
  } catch (runtime_error &e) {}
}

void testSampleRead() {
  cout << "- RUNNING: testSampleRead" << endl;
  JSONDataSource dataSource1(string(TEST_ASSETS_DIR) + "test.json");
  assert(dataSource1.getHeaderSize() == 3);
  assert(dataSource1.getHeaderName(0) == "a");
  assert(dataSource1.getHeaderName(1) == "b");
  assert(dataSource1.getHeaderName(2) == "c");
  vector<string> row1 = dataSource1.getNextRow();
  assert(row1.size() == 3);
  assert(row1[0] == "1");
  assert(row1[1] == "2");
  assert(row1[2] == "3");
  vector<string> row2 = dataSource1.getNextRow();
  assert(row2.size() == 3);
  assert(row2[0] == "4");
  assert(row2[1] == "5");
  assert(row2[2] == "6");

  dataSource1.reset();
  row1 = dataSource1.getNextRow();
  assert(row1.size() == 3);
  assert(row1[0] == "1");
  assert(row1[1] == "2");
  assert(row1[2] == "3");

  dataSource1.reset();
  while (dataSource1.hasNextRow()) {
    assert(dataSource1.getNextRow().size() == 3);
  } // must not throw

  for (size_t i = 1; i <= 3; i++) {
    try {
      JSONDataSource dataSource2(string(TEST_ASSETS_DIR) + "test-error" + to_string(i) +".json");
      while (dataSource2.hasNextRow()) {
        assert(dataSource2.getNextRow().size() == 3);
      }
      assert(false);
    } catch (...) {}
  }

}

void testJSONDataSource() {
  testJSONBlockParser();
  testSampleRead();
}