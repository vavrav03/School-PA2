#include "./data-exporters.h"

using namespace std;

CSVDataExporter::CSVDataExporter(shared_ptr<AbstractDataSource>dataSource, string dstPath) : FileDataExporter(dataSource, dstPath) {}

void CSVDataExporter::exportData() {
  AbstractDataExporter::exportData();
  ofstream file(this->dstPath);
  vector<string> header = this->dataSource->getHeaderVector();
  int headerSize = this->dataSource->getHeaderSize();
  for (int i = 0; i < headerSize; i++) {
    file << header[i];
    if (i < headerSize - 1) {
      file << ",";
    }
  }
  file << endl;
  while (this->dataSource->hasNextRow()) {
    vector<string> row = this->dataSource->getNextRow();
    int rowSize = row.size();
    for (int i = 0; i < rowSize; i++) {
      file << row[i];
      if (i < rowSize - 1) {
        file << ",";
      }
    }
    file << endl;
  }
  file.close();
}
