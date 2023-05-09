#include "data-object.h"
#include <typeinfo>

bool DataObject::operator==(const DataObject &other) const {
  return equals(other);
}

bool DataObject::operator!=(const DataObject &other) const {
  return !equals(other);
}

bool DataObject::operator<(const DataObject &other) const {
  return lessThan(other);
}

bool DataObject::operator>(const DataObject &other) const {
  return other < *this;
}

bool DataObject::operator<=(const DataObject &other) const {
  return !(*this > other);
}

bool DataObject::operator>=(const DataObject &other) const {
  return !(*this < other);
}

bool DataObject::equals(const DataObject &other) const {
  if (typeid(*this) != typeid(other)) {
    return false;
  }
  return true;
}