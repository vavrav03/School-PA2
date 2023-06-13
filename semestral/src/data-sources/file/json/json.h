#ifndef SEMESTRAL_JSON_DATA_SOURCE_H
#define SEMESTRAL_JSON_DATA_SOURCE_H

#include "../file-sources.h"
#include <string>
#include <vector>

/**
 * Custom JSON data source implementation. It requires file to be an array of same JSON objects (it throws error if it is not)
 * nlohmann cannot be used because it does not support streaming of JSON arrays - it requires the whole file to be loaded into memory
 * Representation is memory efficient - only one block is loaded into memory at a time
 */
class JSONDataSource : public FileDataSource {
public:
  JSONDataSource(const std::string &path);

  const std::vector<std::string> getNextRow() override;
  void reset() override;
  static std::pair<std::vector<std::string>, std::vector<std::string> > parseBlockString(const std::string & unparsedJsonObject);
private:
  /**
   * Read first block of JSON array file, set it to nextRow and set header
   * @throws runtime_error if file does not start with [ or if no data is found in the array
   * @return vector of header strings
   */
  void readFirstBlockAndSetHeader();
  /**
   * Get following block in JSON array file
   * @throws runtime_error if there is no block to read - no more data (no starting { or ending } found)
   * @return pair of vectors - first vector is header, second vector is row data
   */
  std::pair<std::vector<std::string>, std::vector<std::string> > readBlock();
  std::vector<std::string> nextRow;
  bool reachedEndOfArray;
};

#endif // SEMESTRAL_JSON_DATA_SOURCE_H