#ifndef SEMESTRAL_JSON_DATA_SOURCE_H
#define SEMESTRAL_JSON_DATA_SOURCE_H

#include "../abstract/abstract.h"
#include <string>
#include <vector>

class JSONDataSource : public AbstractDataSource {
public:
  JSONDataSource(const std::string &path);
  bool hasNextRow() const override;
  const std::vector<std::string> getNextRow() override;
  void reset() override;
private:
  int currentRow;
  std::vector<std::vector<std::string> > rows;
};

#endif // SEMESTRAL_JSON_DATA_SOURCE_H