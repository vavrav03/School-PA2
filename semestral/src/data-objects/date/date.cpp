#include "date.h"

Date::Date(int year, int month, int day)
        : DataObject(), year(year), month(month), day(day) {
}

bool Date::equals(const DataObject &other) const {
  if(!DataObject::equals(other)) {
    return false;
  }
  const Date &otherDate = static_cast<const Date &>(other);
  return year == otherDate.year &&
         month == otherDate.month &&
         day == otherDate.day;
}

bool Date::lessThan(const DataObject &other) const {
  const Date &otherDate = static_cast<const Date &>(other);
  if (year < otherDate.year) {
    return true;
  }
  if (year > otherDate.year) {
    return false;
  }
  if (month < otherDate.month) {
    return true;
  }
  if (month > otherDate.month) {
    return false;
  }
  if (day < otherDate.day) {
    return true;
  }
  if (day > otherDate.day) {
    return false;
  }
  return false;
}