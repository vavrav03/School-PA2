
#include "./json.h"
#include <iostream>

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
  } catch (runtime_error &e) {
  }
}

void testJSONDataSource() {
  testJSONBlockParser();
}