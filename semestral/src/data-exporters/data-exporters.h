#ifndef SEMESTRAL_DATA_EXPORTERS_H
#define SEMESTRAL_DATA_EXPORTERS_H

#include "../data-sources/abstract.h"
#include <fstream>
#

/**
 * Everything that tries to export data to a source outside of this app should inherit from this class.
 * File or connection or whatever, is opened on exportData() call and closed on finish, not in constructor/destructor.
 */
class AbstractDataExporter {
public:
  AbstractDataExporter(std::shared_ptr<AbstractDataSource>dataSource) : dataSource(dataSource) {}

  virtual void exportData() {
    this->dataSource->reset();
  }
  virtual ~AbstractDataExporter(){}
protected:
  std::shared_ptr<AbstractDataSource>dataSource;
};

/**
 * Everything that tries to export data to a file on file system should inherit from this class.
 */
class FileDataExporter : public AbstractDataExporter {
public:
  FileDataExporter(std::shared_ptr<AbstractDataSource>dataSource, std::string dstPath) : AbstractDataExporter(dataSource), dstPath(dstPath) {}
protected:
  std::string dstPath;
};

class CSVDataExporter : public FileDataExporter {
public:
  CSVDataExporter(std::shared_ptr<AbstractDataSource>dataSource, std::string dstPath);

  void exportData() override;
};

class JSONDataExporter : public FileDataExporter {
public:
  JSONDataExporter(std::shared_ptr<AbstractDataSource>dataSource, std::string dstPath);

  void exportData() override;
};
#endif //SEMESTRAL_DATA_EXPORTERS_H