#ifndef SEMESTRAL_DATA_ROW_H
#define SEMESTRAL_DATA_ROW_H

#include "../../data-types/data-type.h"
#include <vector>

class DataRow
{
public:
  DataRow();

  void addField(const DataType *field);
  ~DataRow();
  DataType *operator[](int index) const;

private:
  std::vector<DataType *> data;
};

#endif // SEMESTRAL_DATA_ROW_H