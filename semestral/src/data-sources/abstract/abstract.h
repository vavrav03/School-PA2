#ifndef SEMESTRAL_RESULTSTREAM_H
#define SEMESTRAL_RESULTSTREAM_H

#include <string>
#include <vector>

class AbstractDataSource {
public:
  AbstractDataSource();

  virtual const std::vector<std::string> &getHeader() const;
  const int getHeaderSize() const;

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
  std::vector<std::string> header;
};

#endif // SEMESTRAL_RESULTSTREAM_H
