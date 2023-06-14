#ifndef SEMESTRAL_DATA_EXPORTERS_H
#define SEMESTRAL_DATA_EXPORTERS_H

#include "../data-sources/abstract.h"
#include <fstream>

/**
 * Everything that tries to export data to a source outside of this app should inherit from this class.
 * File or connection or whatever, is opened on exportData() call and closed on finish, not in constructor/destructor.
 */
class AbstractDataExporter {
public:
  explicit AbstractDataExporter(std::unique_ptr<AbstractDataSource>dataSource) : dataSource(std::move(dataSource)) {}

  virtual void exportData() {
    this->dataSource->reset();
  }
  virtual ~AbstractDataExporter() = default;
protected:
  std::unique_ptr<AbstractDataSource>dataSource;
};

/**
 * Everything that tries to export data to a file on file system should inherit from this class.
 */
class FileDataExporter : public AbstractDataExporter {
public:
  FileDataExporter(std::unique_ptr<AbstractDataSource>dataSource, const std::string& dstPath) : AbstractDataExporter(std::move(dataSource)), dstPath(dstPath) {}
protected:
  const std::string & dstPath;
};

class CSVDataExporter : public FileDataExporter {
public:
  CSVDataExporter(std::unique_ptr<AbstractDataSource> dataSource, const std::string &dstPath);

  void exportData() override;
};

class JSONDataExporter : public FileDataExporter {
public:
  JSONDataExporter(std::unique_ptr<AbstractDataSource>dataSource, const std::string& dstPath);

  void exportData() override;
};
#endif //SEMESTRAL_DATA_EXPORTERS_H