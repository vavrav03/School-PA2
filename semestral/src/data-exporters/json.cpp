#include "./data-exporters.h"

using namespace std;

JSONDataExporter::JSONDataExporter(AbstractDataSource *dataSource, std::string dstPath) : FileDataExporter(dataSource, dstPath) {}

void JSONDataExporter::exportData() {
  AbstractDataExporter::exportData();
  ofstream file(this->dstPath);
  vector<string> header = this->dataSource->getHeader();
  file << "[";
  while (this->dataSource->hasNextRow()) {
    vector<string> row = this->dataSource->getNextRow();
    int rowSize = row.size();
    file << "{";
    for (int i = 0; i < rowSize; i++) {
      file << "\"" << header[i] << "\":\"" << row[i] << "\"";
      if (i < rowSize - 1) {
        file << ",";
      }
    }
    file << "}";
    if (this->dataSource->hasNextRow()) {
      file << ",";
    }
  }
  file << "]";
  file.close();
}