#ifndef SEMESTRAL_UTILS_H
#define SEMESTRAL_UTILS_H

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @param map
 * @return vector of strings from keys of passed hashmap. Each string is going to be on index of its value in the hashmap.
 */
std::vector<std::string> indexMapToVector(const std::unordered_map<std::string, int> &map);

/**
 *
 * @param vector
 * @return hashmap of strings from passed vector. Each string is going to be on index of its value in the vector.
 */
std::unordered_map<std::string, int> vectorToIndexMap(const std::vector<std::string> &vector);

#endif //SEMESTRAL_UTILS_H
