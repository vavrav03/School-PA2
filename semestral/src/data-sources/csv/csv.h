#ifndef SEMESTRAL_CSV_DATA_SOURCE_H
#define SEMESTRAL_CSV_DATA_SOURCE_H

#include "../abstract/abstract.h"
#include "../../data-types/data-row/data-row.h"
#include <fstream>

class CSVDataSource: public AbstractDataSource {

public:
  CSVDataSource(const std::string & path);
  bool hasNextRow() const override;
  const DataRow getNextRow() override;
  ~CSVDataSource() override;

private:
  const std::vector <std::string> readUnparsedRow();
  std::ifstream file;
};


#endif //SEMESTRAL_CSV_DATA_SOURCE_H
