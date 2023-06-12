#ifndef SEMESTRAL_FILE_SOURCES_H
#define SEMESTRAL_FILE_SOURCES_H

#include "../abstract.h"

/**
 * Data source for reading from a file.
 */
class FileDataSource : public AbstractDataSource {
public:
  FileDataSource(const std::string &path);
  virtual std::vector<std::string> getHeaderVector() const override;
  virtual std::unordered_map<std::string, size_t> getHeaderMap() const override;
  virtual size_t getHeaderIndex(const std::string &name) const override;
  virtual const std::string& getHeaderName(size_t index) const override;
  virtual size_t getHeaderSize() const override;
  virtual ~FileDataSource();
  void reset() override;
protected:
  std::ifstream file;
  /**
   * Each data source must have a header describing what each column means. This header must be the same size as each row.
   */
  std::unordered_map<std::string, size_t> header;
};

#endif //SEMESTRAL_FILE_SOURCES_H
