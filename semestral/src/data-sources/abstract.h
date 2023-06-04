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
  virtual std::vector<std::string> getHeader() const;

  /**
   *
   * @param name
   * @return index of column with given name.
   */
  int getHeaderIndex(const std::string &name) const;

  /**
   *
   * @param index
   * @return name of column with given index.
   */
  const std::string& getHeaderName(int index) const;

  /**
   *
   * @return number of columns in this relation
   */
  int getHeaderSize() const;

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
  /**
   * Each data source must have a header describing what each column means. This header must be the same size as each row.
   */
  std::unordered_map<std::string, int> header;
};

/**
 * Data source for reading from a file.
 */
class FileDataSource : public AbstractDataSource {
public:
  FileDataSource(const std::string &path);
  virtual ~FileDataSource();
  void reset() override;
protected:
  std::ifstream file;
};

#endif // SEMESTRAL_RESULTSTREAM_H
