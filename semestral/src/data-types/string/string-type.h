#ifndef SEMESTRAL_STRINGTYPE_H
#define SEMESTRAL_STRINGTYPE_H

#include "../data-type.h"
#include <string>

class StringType : public DataType {
public:
  StringType(std::string value);
  std::string getValue() const;
  bool equals(const DataType &other) const override;
  bool lessThan(const DataType &other) const override;
  DataType *clone() const override;

private:
  std::string value;
};

#endif // SEMESTRAL_STRINGTYPE_H
