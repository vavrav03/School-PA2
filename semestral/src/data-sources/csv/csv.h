#ifndef SEMESTRAL_CSV_DATA_SOURCE_H
#define SEMESTRAL_CSV_DATA_SOURCE_H

#include "../abstract.h"
#include <fstream>

class CSVDataSource : public FileDataSource {

public:
  CSVDataSource(const std::string &path);
  bool hasNextRow() const override;
  const std::vector<std::string> getNextRow() override;
  void reset() override;

private:
  void readUnparsedRow();
  std::vector<std::string> nextRow;
};

#endif // SEMESTRAL_CSV_DATA_SOURCE_H
