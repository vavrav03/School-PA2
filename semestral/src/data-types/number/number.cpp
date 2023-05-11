#include "number.h"

Number::Number(int value) : value(value) {}

int Number::getValue() const { return value; }

bool Number::equals(const DataType &other) const {
  if (!DataType::equals(other)) {
    return false;
  }
  const Number &otherNumber = static_cast<const Number &>(other);
  return value == otherNumber.value;
}

bool Number::lessThan(const DataType &other) const {
  const Number &otherNumber = static_cast<const Number &>(other);
  return value < otherNumber.value;
}

DataType *Number::clone() const { return new Number(*this); }