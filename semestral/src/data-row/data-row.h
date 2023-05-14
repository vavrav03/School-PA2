#ifndef SEMESTRAL_DATA_ROW_H
#define SEMESTRAL_DATA_ROW_H

#include <vector>
#include <string>

class DataRow {
public:
  DataRow();

  void addField(const std::string & field);
  ~DataRow();
  const std::string &operator[](int index) const;

private:
  std::vector<std::string> data;
};

#endif // SEMESTRAL_DATA_ROW_H