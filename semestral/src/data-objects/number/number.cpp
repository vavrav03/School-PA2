#include "number.h"

Number::Number(int value) : value(value) {}

int Number::getValue() const {
  return value;
}

bool Number::equals(const DataObject &other) const {
  if(!DataObject::equals(other)) {
    return false;
  }
  const Number &otherNumber = static_cast<const Number &>(other);
  return value == otherNumber.value;
}

bool Number::lessThan(const DataObject &other) const {
  const Number &otherNumber = static_cast<const Number &>(other);
  return value < otherNumber.value;
}