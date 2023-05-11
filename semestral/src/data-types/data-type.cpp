#include "data-type.h"
#include <typeinfo>

bool DataType::operator==(const DataType &other) const {
  return equals(other);
}

bool DataType::operator!=(const DataType &other) const {
  return !equals(other);
}

bool DataType::operator<(const DataType &other) const {
  return lessThan(other);
}

bool DataType::operator>(const DataType &other) const {
  return other < *this;
}

bool DataType::operator<=(const DataType &other) const {
  return !(*this > other);
}

bool DataType::operator>=(const DataType &other) const {
  return !(*this < other);
}

bool DataType::equals(const DataType &other) const {
  if (typeid(*this) != typeid(other)) {
    return false;
  }
  return true;
}