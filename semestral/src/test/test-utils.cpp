#include "../utils/utils.h"
#include <iostream>

using namespace std;

void testPathUtils() {
  cout << "RUNNING: testPathUtils" << endl;
  assert(getNameFromPath("test.json") == "test.json");
  assert(getNameFromPath("./test.json") == "test.json");
  assert(getNameFromPath("/test.json") == "test.json");
  assert(getNameFromPath("test.json.json") == "test.json.json");
  assert(getNameFromPath("test") == "test");

  assert(getExtensionFromPath("test.json") == "json");
  assert(getExtensionFromPath("./test.json") == "json");
  assert(getExtensionFromPath("/test.json") == "json");
  assert(getExtensionFromPath("test.json.json") == "json.json");
  assert(getExtensionFromPath("test") == "");
  assert(getExtensionFromPath("test/json/test.json") == "json");

  assert(getNameWithoutExtension("test.json") == "test");
  assert(getNameWithoutExtension("./test.json") == "test");
  assert(getNameWithoutExtension("/test.json") == "test");
  assert(getNameWithoutExtension("test.json.json") == "test");
  assert(getNameWithoutExtension("test") == "test");
}

void testUtils() {
}