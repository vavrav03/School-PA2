#ifndef SEMESTRAL_DATA_OBJECT_H
#define SEMESTRAL_DATA_OBJECT_H

/**
 * Base class for all data objects.
 * All data objects must implement comparison operators.
 * Types which cannot be compared like complex number are not supported
 * and must be represented by a different type, e.g. a string.
 *
 */
class DataType {

public:
  virtual ~DataType() {}

  DataType() = default;
  DataType(const DataType &other) = default;
  DataType &operator=(const DataType &other) = default;
  bool operator==(const DataType &other) const;
  bool operator!=(const DataType &other) const;
  bool operator<(const DataType &other) const;
  bool operator>(const DataType &other) const;
  bool operator<=(const DataType &other) const;
  bool operator>=(const DataType &other) const;
  virtual bool equals(const DataType &other) const;
  virtual bool lessThan(const DataType &other) const = 0;
  virtual DataType *clone() const = 0;
};

#endif
