#include "./rename.h"

#include <vector>
#include <string>

using namespace std;

RenameExpression::RenameExpression(AbstractDataSource& dataSource, const HeaderValueContainer & translations) : dataSource(dataSource)
{
  vector<string> newHeader;
  for (int i = 0; i < dataSource.getHeader().size(); i++)
  {
    if(translations.hasHeaderValue(dataSource.getHeader()[i]))
    {
      newHeader.push_back(translations[dataSource.getHeader()[i]]);
    }
    else
    {
      newHeader.push_back(dataSource.getHeader()[i]);
    }
  }
}

RenameExpression::~RenameExpression()
{
}

const DataRow &RenameExpression::getHeader() const
{
  return this->renamedHeader;
}

bool RenameExpression::hasNextRow() const
{
  return this->dataSource.hasNextRow();
}

const DataRow RenameExpression::getNextRow()
{
  return this->dataSource.getNextRow();
}
