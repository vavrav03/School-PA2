#ifndef SEMESTRAL_NUMBER_H
#define SEMESTRAL_NUMBER_H

#include "../data-object.h"

class Number: public DataObject{

  public:
    Number(int value);
    int getValue() const;
    bool equals(const DataObject &other) const override;
    bool lessThan(const DataObject &other) const override;

  private:
    int value;
};


#endif //SEMESTRAL_NUMBER_H
