#include "timestamp.h"
#include "../data-type.h"

Timestamp::Timestamp(int year, int month, int day, int hour, int minute, int second) : date(year, month, day),
                                                                                       time(hour, minute, second) {}

int Timestamp::getYear() const
{
  return date.getYear();
}

int Timestamp::getMonth() const
{
  return date.getMonth();
}

int Timestamp::getDay() const
{
  return date.getDay();
}

int Timestamp::getHour() const
{
  return time.getHour();
}

int Timestamp::getMinute() const
{
  return time.getMinute();
}

int Timestamp::getSecond() const
{
  return time.getSecond();
}

bool Timestamp::equals(const DataType &other) const
{
  if (!DataType::equals(other))
  {
    return false;
  }
  const Timestamp &otherTimestamp = static_cast<const Timestamp &>(other);
  return date.equals(otherTimestamp.date) && time.equals(otherTimestamp.time);
}

bool Timestamp::lessThan(const DataType &other) const
{
  const Timestamp &otherTimestamp = static_cast<const Timestamp &>(other);
  if (date.lessThan(otherTimestamp.date))
  {
    return true;
  }
  if (date.equals(otherTimestamp.date) && time.lessThan(otherTimestamp.time))
  {
    return true;
  }
  return false;
}

DataType *Timestamp::clone() const
{
  return new Timestamp(*this);
}
