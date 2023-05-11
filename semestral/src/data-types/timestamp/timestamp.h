#ifndef SEMESTRAL_TIMESTAMP_H
#define SEMESTRAL_TIMESTAMP_H

#include "../data-type.h"
#include "../date/date.h"
#include "../time/time.h"

class Timestamp: public DataType {
public:
  Timestamp(int year, int month, int day, int hour, int minute, int second);
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  bool equals(const DataType &other) const override;
  bool lessThan(const DataType &other) const override;

private:
  Date date;
  Time time;
};


#endif //SEMESTRAL_TIMESTAMP_H
