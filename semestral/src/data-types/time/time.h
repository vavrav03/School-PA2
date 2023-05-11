#ifndef SEMESTRAL_TIME_H
#define SEMESTRAL_TIME_H
#include "../data-type.h"

class Time: public DataType{

public:
  Time(int hour, int minute, int second);
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  bool equals(const DataType &other) const override;
  bool lessThan(const DataType &other) const override;
  DataType *clone() const override;
private:
  int hour;
  int minute;
  int second;
};


#endif //SEMESTRAL_TIME_H
