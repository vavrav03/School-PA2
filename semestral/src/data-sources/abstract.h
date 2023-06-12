#ifndef SEMESTRAL_RESULTSTREAM_H
#define SEMESTRAL_RESULTSTREAM_H

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <memory>

/**
 * Everything that produces relational data should inherit from this class.
 */
class AbstractDataSource {
public:
  AbstractDataSource() = default;

  /**
   *
   * @return vector of strings describing what each column means.
   */
  virtual std::vector<std::string> getHeaderVector() const = 0;

  virtual std::unordered_map<std::string, size_t> getHeaderMap() const = 0;

  /**
   *
   * @param name
   * @throws std::runtime_error if there is no column with given name.
   * @return index of column with given name.
   */
  virtual size_t getHeaderIndex(const std::string &name) const = 0;

  /**
   *
   * @param index
   * @return name of column with given index.
   */
  virtual const std::string& getHeaderName(size_t index) const = 0;

  /**
   *
   * @return number of columns in this relation
   */
  virtual size_t getHeaderSize() const = 0;

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
  virtual ~AbstractDataSource() = default;
};



#endif // SEMESTRAL_RESULTSTREAM_H
