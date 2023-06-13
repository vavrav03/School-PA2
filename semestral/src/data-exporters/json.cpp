#include "./data-exporters.h"

using namespace std;

JSONDataExporter::JSONDataExporter(shared_ptr<AbstractDataSource> dataSource, std::string dstPath) : FileDataExporter(
        dataSource, dstPath) {}

void JSONDataExporter::exportData() {
  AbstractDataExporter::exportData();
  ofstream file(this->dstPath);
  vector<string> header = this->dataSource->getHeaderVector();
  file << "[";
  vector<string> row;
  bool first = true;
  while (!(row = this->dataSource->getNextRow()).empty()) {
    size_t rowSize = row.size();
    if (!first) {
      file << ",";
    }
    file << "{";
    for (size_t i = 0; i < rowSize; i++) {
      file << "\"" << header[i] << "\":\"" << row[i] << "\"";
      if (i < rowSize - 1) {
        file << ",";
      }
    }
    file << "}";
    first = false;
  }
  file << "]";
  file.close();
}