#ifndef SEMESTRAL_CSV_DATA_SOURCE_H
#define SEMESTRAL_CSV_DATA_SOURCE_H

#include "../abstract.h"
#include <fstream>

/**
 * Class responsible for reading CSV files. It does not assume correctness of a file - it checks for it.
 * It does not read the entire file into memory. Lines are read one by one only if needed
 */
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
