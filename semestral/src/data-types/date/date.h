#ifndef SEMESTRAL_DATE_H
#define SEMESTRAL_DATE_H

#include "../data-type.h"

class Date : public DataType {

public:
  Date(int year, int month, int day);
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  bool equals(const DataType &other) const override;
  bool lessThan(const DataType &other) const override;
private:
  int year;
  int month;
  int day;
};


#endif //SEMESTRAL_DATE_H
