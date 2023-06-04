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
  cout << projection.toSQL() << endl;
  assert(toLowerCase(projection.toSQL()) == "select height,age from (select * from a) as b");
}

void testExpression() {
  testProjection();
}
