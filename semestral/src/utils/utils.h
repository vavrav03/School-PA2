#ifndef SEMESTRAL_UTILS_H
#define SEMESTRAL_UTILS_H

#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::string> indexMapToVector(const std::unordered_map<std::string, int> &map);

std::unordered_map<std::string, int> vectorToIndexMap(const std::vector<std::string> &vector);

#endif //SEMESTRAL_UTILS_H
