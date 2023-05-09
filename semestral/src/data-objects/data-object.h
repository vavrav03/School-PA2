#ifndef SEMESTRAL_DATA_OBJECT_H
#define SEMESTRAL_DATA_OBJECT_H

/**
 * Base class for all data objects.
 * All data objects must implement comparison operators.
 * Types which cannot be compared like complex number are not supported
 * and must be represented by a different type, e.g. a string.
 *
 */
class DataObject {

public:
  virtual ~DataObject() {}

  DataObject() = default;
  DataObject(const DataObject &other) = default;
  DataObject &operator=(const DataObject &other) = default;
  bool operator==(const DataObject &other) const;
  bool operator!=(const DataObject &other) const;
  bool operator<(const DataObject &other) const;
  bool operator>(const DataObject &other) const;
  bool operator<=(const DataObject &other) const;
  bool operator>=(const DataObject &other) const;
  virtual bool equals(const DataObject &other) const;
  virtual bool lessThan(const DataObject &other) const = 0;
};

#endif
