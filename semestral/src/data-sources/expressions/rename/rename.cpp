#include "./rename.h"
#include <string>

using namespace std;

RenameExpression::RenameExpression(AbstractDataSource& dataSource, const std::unordered_map<const std::string, const std::string, std::hash<string>> &renameCriteria) : dataSource(dataSource)
{
  const vector<string> & oldHeader = dataSource.getHeader();
  for (const string & oldName : oldHeader) {
    if (renameCriteria.find(oldName) != renameCriteria.end()) {
      this->renamedHeader.push_back(renameCriteria.at(oldName));
    } else {
      this->renamedHeader.push_back(oldName);
    }
  }
}

RenameExpression::~RenameExpression()
{
}

const vector<string> &RenameExpression::getHeader() const
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
