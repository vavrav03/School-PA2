#ifndef SEMESTRAL_TIME_H
#define SEMESTRAL_TIME_H
#include "../data-object.h"

class Time: public DataObject{

public:
  Time(int hour, int minute, int second);
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  bool equals(const DataObject &other) const override;
  bool lessThan(const DataObject &other) const override;
private:
  int hour;
  int minute;
  int second;
};


#endif //SEMESTRAL_TIME_H
