#ifndef SEMESTRAL_TIMESTAMP_H
#define SEMESTRAL_TIMESTAMP_H

#include "../data-object.h"
#include "../date/date.h"
#include "../time/time.h"

class Timestamp: public DataObject {
public:
  Timestamp(int year, int month, int day, int hour, int minute, int second);
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  bool equals(const DataObject &other) const override;
  bool lessThan(const DataObject &other) const override;

private:
  Date date;
  Time time;
};


#endif //SEMESTRAL_TIMESTAMP_H
