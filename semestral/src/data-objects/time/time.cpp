#include "time.h"

Time::Time(int hour, int minute, int second)
        : DataObject(), hour(hour), minute(minute), second(second) {
}

bool Time::equals(const DataObject &other) const {
  if(!DataObject::equals(other)) {
    return false;
  }
  const Time &otherTime = static_cast<const Time &>(other);
  return hour == otherTime.hour &&
         minute == otherTime.minute &&
         second == otherTime.second;
}

bool Time::lessThan(const DataObject &other) const {
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