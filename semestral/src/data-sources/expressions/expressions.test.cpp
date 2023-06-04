#include "./expressions.h"
#include "../../../src/test/test_list.h"
#include "../../data-sources/csv/csv.h"
#include <iostream>

using namespace std;

void testProjection() {
  string t = string(TEST_ASSETS_DIR) + "test.csv";
  auto dataSource = make_shared<CSVDataSource>(string(TEST_ASSETS_DIR) + "test.csv");
  vector<string> headers(2);
  headers[0] = "height";
  headers[1] = "age";
  auto wrapper = make_shared<DataSourceExpressionWrapper>(dataSource, "a");
  ProjectionExpression projection(wrapper, headers, "b");
  assert(toLowerCase(projection.toSQL()) == "select height,age from (select * from a) as b");
  assert(projection.getHeaderSize() == 2);
  assert(projection.hasNextRow());
  vector<string> rows = projection.getNextRow();
  assert(projection.getHeaderIndex("height") == 0);
  assert(projection.getHeaderIndex("age") == 1);
  assert(projection.getHeaderName(0) == "height");
  assert(projection.getHeaderName(1) == "age");
  assert(rows[0] == "180");
  assert(rows[1] == "25");
  assert(!projection.hasNextRow());
}

void testExpression() {
  testProjection();
}
