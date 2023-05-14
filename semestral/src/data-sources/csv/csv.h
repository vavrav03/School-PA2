#ifndef SEMESTRAL_CSV_DATA_SOURCE_H
#define SEMESTRAL_CSV_DATA_SOURCE_H

#include "../abstract/data-row.h"
#include "../abstract/abstract.h"
#include <fstream>

class CSVDataSource : public AbstractDataSource {

public:
  CSVDataSource(const std::string &path);
  bool hasNextRow() const override;
  const DataRow getNextRow() override;
  ~CSVDataSource() override;

private:
  void readUnparsedRow();
  std::vector<std::string> nextRow;
  std::ifstream file;
};

#endif // SEMESTRAL_CSV_DATA_SOURCE_H
