#ifndef SEMESTRAL_VARIABLE_DATA_SOURCE_H
#define SEMESTRAL_VARIABLE_DATA_SOURCE_H

#include "../abstract/data-row.h"
#include "../abstract/abstract.h"

class VariableDataSource : public AbstractDataSource
{
public:
  VariableDataSource();
  bool hasNextRow() const override;
  const DataRow getNextRow() override;
private: 
  int currentRow;
  std::vector<DataRow> rows;
};


#endif // SEMESTRAL_VARIABLE_DATA_SOURCE_H