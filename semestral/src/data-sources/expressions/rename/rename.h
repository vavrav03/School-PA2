#ifndef SEMESTRAL_RENAME_EXPRESSION_H
#define SEMESTRAL_RENAME_EXPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../abstract/unary-expression.h"
#include "../../abstract/header-value-container.h"

class RenameExpression : public AbstractUnaryExpression
{
public:
  RenameExpression(AbstractDataSource* dataSource, const HeaderValueContainer &renameCriteria);
  const std::vector<std::string> &getHeader() const override;
  bool hasNextRow() const override;
  const std::vector<std::string> getNextRow() override;
  std::string toSQL() const override;

private:
  std::vector<std::string> renamedHeader;
};

#endif // SEMESTRAL_RENAME_EXPRESSION_H