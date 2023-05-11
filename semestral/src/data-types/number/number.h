#ifndef SEMESTRAL_NUMBER_H
#define SEMESTRAL_NUMBER_H

#include "../data-type.h"

class Number : public DataType {

public:
  Number(int value);
  int getValue() const;
  bool equals(const DataType &other) const override;
  bool lessThan(const DataType &other) const override;
  DataType *clone() const override;

private:
  int value;
};

#endif // SEMESTRAL_NUMBER_H
