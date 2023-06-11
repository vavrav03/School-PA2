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

string join(const vector<string> &vector, const string &delimiter) {
  string result;
  for (int i = 0; i < vector.size(); i++) {
    result += vector[i];
    if (i != vector.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}

string toLowerCase(const string &stringToConvert) {
  string result = stringToConvert;
  for (char &c : result) {
    c = tolower(c);
  }
  return result;
}

void printStringVector(const vector<string> &vector) {
  for (const string &item: vector) {
    cout << item << " ";
  }
  cout << endl;
}

bool equalsStringVectors(const vector<string> &a, const vector<string> &b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}