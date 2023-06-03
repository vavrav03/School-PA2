#ifndef SEMESTRAL_JSON_DATA_SOURCE_H
#define SEMESTRAL_JSON_DATA_SOURCE_H

#include "../abstract/abstract.h"
#include <string>

class JsonDataSource : public AbstractDataSource
{
public:
  JsonDataSource(const std::string &path);
  bool hasNextRow() const override;
  const vector<string> getNextRow() override;
private:
  int currentRow;
  std::vector<vector<string>> rows;
};

#endif // SEMESTRAL_JSON_DATA_SOURCE_H