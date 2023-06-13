
#include "../data-sources/file/json/json.h"
#include <iostream>
#include "test_list.h"
#include "../utils/utils.h"

using namespace std;

void testJSONBlockParser() {
  cout << "- RUNNING: testJSONBlockParser" << endl;
  auto block = JSONDataSource::parseBlockString("\"a\": 1, \"b\": 2");
  assert(equalsVectors(block.first, vector<string>{"a", "b"}));
  assert(equalsVectors(block.second, vector<string>{"1", "2"}));

  block = JSONDataSource::parseBlockString("\"a\": 1");
  assert(block.first[0] == "a");
  assert(block.second[0] == "1");

  block = JSONDataSource::parseBlockString("\"a\": 1, \n\t     \"b\":    \"2\"");
  assert(equalsVectors(block.first, vector<string>{"a", "b"}));
  assert(equalsVectors(block.second, vector<string>{"1", "2"}));

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
  assert(equalsVectors(dataSource1.getHeaderVector(), vector<string>{"a", "b", "c"}));
  assert(equalsVectors(dataSource1.getNextRow(), vector<string>{"1", "2", "3"}));
  assert(equalsVectors(dataSource1.getNextRow(), vector<string>{"4", "5", "6"}));
  assert(dataSource1.getNextRow().empty());
  cout << "- RUNNING: testSampleRead2" << endl;

  dataSource1.reset();
  dataSource1.reset();
  dataSource1.reset();
  dataSource1.reset();
  assert(equalsVectors(dataSource1.getNextRow(), vector<string>{"1", "2", "3"}));
  assert(equalsVectors(dataSource1.getNextRow(), vector<string>{"4", "5", "6"}));
  assert(dataSource1.getNextRow().empty());

  dataSource1.reset();
  vector<string> result;
  while (!(result = dataSource1.getNextRow()).empty()) {
    assert(result.size() == 3);
  }

  for (size_t i = 1; i <= 3; i++) {
    try {
      JSONDataSource dataSource2(string(TEST_ASSETS_DIR) + "test-error" + to_string(i) + ".json");
      while (!(result = dataSource2.getNextRow()).empty()) {
        assert(result.size() == 3);
      }
      assert(false);
    } catch (...) {}
  }
}

void testJSONDataSource() {
  testJSONBlockParser();
  testSampleRead();
}