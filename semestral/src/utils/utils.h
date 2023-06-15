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
template<typename T>
std::vector<T> indexMapToVector(const std::unordered_map<T, size_t> &map) {
  std::vector<T> vector(map.size());
  vector.reserve(map.size());
  for (auto &pair : map) {
    vector[pair.second] = pair.first;
  }
  return vector;
}

/**
 *
 * @param vector
 * @return hashmap of strings from passed vector. Each string is going to be on index of its value in the vector.
 */
template<typename T>
std::unordered_map<T, size_t> vectorToIndexMap(const std::vector<T> &vector) {
  std::unordered_map<T, size_t> map(vector.size());
  map.reserve(vector.size());
  for (size_t i = 0; i < vector.size(); i++) {
    map[vector[i]] = i;
  }
  return map;
}

std::string toLowerCase(const std::string &stringToConvert);

template<typename T>
void printVector(const std::vector<T> &vector) {
  for (const T &item : vector) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

template<typename T>
bool equalsVectors(const std::vector<T> &a, const std::vector<T> &b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

template<typename T>
std::vector<T> joinVectors(const std::vector<T> &a, const std::vector<T> &b) {
  std::vector<T> result(a.size() + b.size());
  result.reserve(a.size() + b.size());
  for (size_t i = 0; i < a.size(); i++) {
    result[i] = a[i];
  }
  for (size_t i = 0; i < b.size(); i++) {
    result[i + a.size()] = b[i];
  }
  return result;
}

/**
 *
 * @param a
 * @param b
 * @return true if at least one of the maps contains same key as the other one
 */
template<typename T>
bool mapsContainSameKey(const std::unordered_map<T, size_t> &a, const std::unordered_map<T, size_t> &b) {
  for (auto &pair : a) {
    if (b.find(pair.first) != b.end()) {
      return true;
    }
  }
  for (auto &pair : b) {
    if (a.find(pair.first) != a.end()) {
      return true;
    }
  }
  return false;
}

template<typename T>
std::vector<T> getSameKeys(const std::unordered_map<T, size_t> &a, const std::unordered_map<T, size_t> &b) {
  std::vector<T> result;
  for (auto &pair : a) {
    if (b.find(pair.first) != b.end()) {
      result.push_back(pair.first);
    }
  }
  return result;
}

template<typename T>
std::unordered_map<T, size_t> joinIndexMaps(const std::unordered_map<T, size_t> &a,
                                            const std::unordered_map<T, size_t> &b) {
  std::unordered_map<T, size_t> result(a.size() + b.size());
  for (auto &pair : a) {
    result[pair.first] = pair.second;
  }
  int index = a.size();
  for (int i = 0; i < b.size(); i++) {
    for (auto &pair : b) {
      if (pair.second == i && result.find(pair.first) == result.end()) {
        result[pair.first] = index++;
      }
    }
  }
  return result;
}

template<typename T>
const T &findValueOrThrowInIndexMap(const std::unordered_map<T, size_t> &map, const size_t index) {
  for (auto &pair : map) {
    if (pair.second == index) {
      return pair.first;
    }
  }
  throw std::runtime_error("Index not found");
}

/**
 *
 * @param path
 * @return name + extension
 */
std::string getNameFromPath(const std::string &path);
std::string getExtensionFromPath(const std::string &path);
std::string getNameWithoutExtension(const std::string &filename);

#endif //SEMESTRAL_UTILS_H
