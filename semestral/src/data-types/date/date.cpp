#include "date.h"

Date::Date(int year, int month, int day)
        : DataType(), year(year), month(month), day(day) {
}

int Date::getYear() const {
  return year;
}

int Date::getMonth() const {
  return month;
}

int Date::getDay() const {
  return day;
}

bool Date::equals(const DataType &other) const {
  if(!DataType::equals(other)) {
    return false;
  }
  const Date &otherDate = static_cast<const Date &>(other);
  return year == otherDate.year &&
         month == otherDate.month &&
         day == otherDate.day;
}

bool Date::lessThan(const DataType &other) const {
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

DataType *Date::clone() const {
  return new Date(*this);
}