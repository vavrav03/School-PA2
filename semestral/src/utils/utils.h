#ifndef SEMESTRAL_UTILS_H
#define SEMESTRAL_UTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

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
std::string join(const std::vector<std::string> &vector, const std::string &delimiter);
std::string toLowerCase(const std::string &string);
void printStringVector(const std::vector<std::string> &vector);
bool equalsStringVectors(const std::vector<std::string> &a, const std::vector<std::string> &b);
std::vector<std::string> joinStringVectors(const std::vector<std::string> &a, const std::vector<std::string> &b);
/**
 *
 * @param a
 * @param b
 * @return true if at least one of the maps contains same key as the other one
 */
bool mapsContainSameKey(const std::unordered_map<std::string, int> &a, const std::unordered_map<std::string, int> &b);
#endif //SEMESTRAL_UTILS_H
