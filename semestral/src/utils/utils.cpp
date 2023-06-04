#include "./utils.h"

using namespace std;

vector<string> indexMapToVector(const unordered_map<string, int> &map) {
  vector<string> vector(map.size());
  vector.reserve(map.size());
  for (auto &pair: map) {
    vector[pair.second] = pair.first;
  }
  return vector;
}

unordered_map<string, int> vectorToIndexMap(const vector<string> &vector){
  unordered_map<string, int> map(vector.size());
  map.reserve(vector.size());
  for(int i = 0; i < vector.size(); i++){
    map[vector[i]] = i;
  }
  return map;
}