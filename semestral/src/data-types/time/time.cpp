#include "time.h"

Time::Time(int hour, int minute, int second)
        : DataType(), hour(hour), minute(minute), second(second) {
}

bool Time::equals(const DataType &other) const {
  if(!DataType::equals(other)) {
    return false;
  }
  const Time &otherTime = static_cast<const Time &>(other);
  return hour == otherTime.hour &&
         minute == otherTime.minute &&
         second == otherTime.second;
}

bool Time::lessThan(const DataType &other) const {
  const Time &otherTime = static_cast<const Time &>(other);
  if (hour < otherTime.hour) {
    return true;
  }
  if (hour > otherTime.hour) {
    return false;
  }
  if (minute < otherTime.minute) {
    return true;
  }
  if (minute > otherTime.minute) {
    return false;
  }
  if (second < otherTime.second) {
    return true;
  }
  if (second > otherTime.second) {
    return false;
  }
  return false;
}