#ifndef SEMESTRAL_STRINGTYPE_H
#define SEMESTRAL_STRINGTYPE_H

#include "../data-object.h"
#include <string>

class StringType : public DataObject {
public:
  StringType(std::string value);
  std::string getValue() const;
  bool equals(const DataObject &other) const override;
  bool lessThan(const DataObject &other) const override;

private:
  std::string value;

};


#endif //SEMESTRAL_STRINGTYPE_H
