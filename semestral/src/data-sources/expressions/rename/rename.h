#ifndef SEMESTRAL_RENAME_EXPRESSION_H
#define SEMESTRAL_RENAME_EXPRESSION_H

#include "../../../data-types/data-row/data-row.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "../../abstract/abstract.h"

class RenameExpression : public AbstractDataSource
{
public:
  RenameExpression(AbstractDataSource& dataSource, const std::unordered_map<const std::string, const std::string, std::hash<std::string>> &renameCriteria);
  ~RenameExpression();
  const std::vector<std::string> &getHeader() const;
  bool hasNextRow() const;
  const DataRow getNextRow();

private:
  AbstractDataSource& dataSource;
  std::vector<std::string> renamedHeader;
};

#endif // SEMESTRAL_RENAME_EXPRESSION_H