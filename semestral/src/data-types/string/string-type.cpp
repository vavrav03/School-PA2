#include "string-type.h"

StringType::StringType(std::string value) : value(value) {}

std::string StringType::getValue() const { return value; }

bool StringType::equals(const DataType &other) const {
  if (!DataType::equals(other)) {
    return false;
  }
  const StringType &otherString = static_cast<const StringType &>(other);
  return value == otherString.value;
}

bool StringType::lessThan(const DataType &other) const {
  const StringType &otherString = static_cast<const StringType &>(other);
  return value < otherString.value;
}

DataType *StringType::clone() const { return new StringType(value); }