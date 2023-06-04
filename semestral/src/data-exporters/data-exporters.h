#ifndef SEMESTRAL_DATA_EXPORTERS_H
#define SEMESTRAL_DATA_EXPORTERS_H

#include "../data-sources/abstract.h"
#include <fstream>

class AbstractDataExporter {
public:
  AbstractDataExporter(AbstractDataSource *dataSource) : dataSource(dataSource) {}

  virtual void exportData() {
    this->dataSource->reset();
  }
  virtual ~AbstractDataExporter(){}
protected:
  AbstractDataSource *dataSource;
};

class FileDataExporter : public AbstractDataExporter {
public:
  FileDataExporter(AbstractDataSource *dataSource, std::string dstPath) : AbstractDataExporter(dataSource), dstPath(dstPath) {}
protected:
  std::string dstPath;
};

class CSVDataExporter : public FileDataExporter {
public:
  CSVDataExporter(AbstractDataSource *dataSource, std::string dstPath);

  void exportData() override;
  ~CSVDataExporter() override;
};

//class JSONDataExporter : public FileDataExporter {
//public:
//  JSONDataExporter(AbstractDataSource *dataSource, std::string dstPath);
//
//  void exportData() override;
//  ~JSONDataExporter() override;
//};
#endif //SEMESTRAL_DATA_EXPORTERS_H