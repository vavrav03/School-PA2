#ifndef SEMESTRAL_RESULTSTREAM_H
#define SEMESTRAL_RESULTSTREAM_H

#include "../../data-row/data-row.h"
#include <string>
#include <vector>

class AbstractDataSource {
public:
  AbstractDataSource();
  virtual const std::vector<std::string> &getHeader() const;
  const int getHeaderSize() const;
  virtual bool hasNextRow() const = 0;
  virtual const DataRow getNextRow() = 0;
  virtual ~AbstractDataSource();

protected:
  std::vector<std::string> header;
};

#endif // SEMESTRAL_RESULTSTREAM_H
