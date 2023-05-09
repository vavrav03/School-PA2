#include "stringType.h"

StringType::StringType(std::string value) : value(value) {}

std::string StringType::getValue() const {
  return value;
}

bool StringType::equals(const DataObject &other) const {
  if(!DataObject::equals(other)) {
    return false;
  }
  const StringType &otherString = static_cast<const StringType &>(other);
  return value == otherString.value;
}

bool StringType::lessThan(const DataObject &other) const {
  const StringType &otherString = static_cast<const StringType &>(other);
  return value < otherString.value;
}