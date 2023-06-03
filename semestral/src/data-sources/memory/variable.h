#ifndef SEMESTRAL_VARIABLE_DATA_SOURCE_H
#define SEMESTRAL_VARIABLE_DATA_SOURCE_H

#include "../abstract/abstract.h"

class VariableDataSource : public AbstractDataSource {
public:
  VariableDataSource();
  bool hasNextRow() const override;
  const std::vector<std::string> getNextRow() override;
private:
  int currentRow;
  std::vector<std::vector<std::string> > rows;
};


#endif // SEMESTRAL_VARIABLE_DATA_SOURCE_H