#include "./expressions.h"
#include "../../../src/test/test_list.h"
#include "../../data-sources/csv/csv.h"
#include <iostream>

using namespace std;

void testProjection() {
  string t = string(TEST_ASSETS_DIR) + "test.csv";
  auto dataSource = make_shared<CSVDataSource>(string(TEST_ASSETS_DIR) + "test.csv");
  vector<string> headers(2);
  headers[0] = "vyska";
  headers[1] = "age";
  auto wrapper = make_shared<DataSourceExpressionWrapper>(dataSource, "a");
  unordered_map<string, string> aliases;
  aliases["vyska"] = "height";
  ProjectionExpression projection(wrapper, headers, aliases, "b");
  cout << projection.toSQL() << endl;
  assert(toLowerCase(projection.toSQL()) == "select height as vyska, age from (select * from a) as b");
  assert(projection.getHeaderSize() == 2);
  assert(projection.hasNextRow());
  vector<string> rows = projection.getNextRow();
  assert(projection.getHeaderIndex("vyska") == 0);
  assert(projection.getHeaderIndex("age") == 1);
  assert(projection.getHeaderName(0) == "vyska");
  assert(projection.getHeaderName(1) == "age");
  assert(rows[0] == "180");
  assert(rows[1] == "25");
  assert(!projection.hasNextRow());
}

void testExpression() {
  testProjection();
}
