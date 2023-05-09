#ifndef SEMESTRAL_DATE_H
#define SEMESTRAL_DATE_H

#include "../data-object.h"

class Date : public DataObject {

public:
  Date(int year, int month, int day);
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  bool equals(const DataObject &other) const override;
  bool lessThan(const DataObject &other) const override;
private:
  int year;
  int month;
  int day;
};


#endif //SEMESTRAL_DATE_H
