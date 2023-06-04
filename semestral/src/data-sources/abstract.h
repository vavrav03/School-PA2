#ifndef SEMESTRAL_RESULTSTREAM_H
#define SEMESTRAL_RESULTSTREAM_H

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

/**
 * Everything that produces relational data should inherit from this class.
 */
class AbstractDataSource {
public:
  AbstractDataSource();

  /**
   *
   * @return vector of strings describing what each column means.
   */
  virtual std::vector<std::string> getHeaderVector() const = 0;

  virtual std::unordered_map<std::string, int> getHeaderMap() const = 0;

  /**
   *
   * @param name
   * @throws std::runtime_error if there is no column with given name.
   * @return index of column with given name.
   */
  virtual int getHeaderIndex(const std::string &name) const = 0;

  /**
   *
   * @param index
   * @return name of column with given index.
   */
  virtual const std::string& getHeaderName(int index) const = 0;

  /**
   *
   * @return number of columns in this relation
   */
  virtual int getHeaderSize() const = 0;

  /**
   *
   * @return true if there is at least one more row to be read.
   */
  virtual bool hasNextRow() const = 0;

  /**
   * @throws std::runtime_error if there is no next row.
   * @return the next row of data as a vector of strings.
   */
  virtual const std::vector<std::string> getNextRow() = 0;

  /**
   * Resets the data source to the beginning of whatever it is iterating over.
   */
  virtual void reset() = 0;
  virtual ~AbstractDataSource();

protected:
};

/**
 * Data source for reading from a file.
 */
class FileDataSource : public AbstractDataSource {
public:
  FileDataSource(const std::string &path);
  virtual std::vector<std::string> getHeaderVector() const override;
  virtual std::unordered_map<std::string, int> getHeaderMap() const override;
  virtual int getHeaderIndex(const std::string &name) const override;
  virtual const std::string& getHeaderName(int index) const override;
  virtual int getHeaderSize() const override;
  virtual ~FileDataSource();
  void reset() override;
protected:
  std::ifstream file;
  /**
   * Each data source must have a header describing what each column means. This header must be the same size as each row.
   */
  std::unordered_map<std::string, int> header;
};

#endif // SEMESTRAL_RESULTSTREAM_H
