#ifndef SEMESTRAL_RENAME_EXPRESSION_H
#define SEMESTRAL_RENAME_EXPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../../abstract/data-row.h"
#include "../../abstract/abstract.h"
#include "../../abstract/header-value-container.h"

class RenameExpression : public AbstractDataSource
{
public:
  RenameExpression(AbstractDataSource& dataSource, const HeaderValueContainer &renameCriteria);
  ~RenameExpression();
  const DataRow &getHeader() const;
  bool hasNextRow() const;
  const DataRow getNextRow();

private:
  AbstractDataSource& dataSource;
  DataRow renamedHeader;
};

#endif // SEMESTRAL_RENAME_EXPRESSION_H