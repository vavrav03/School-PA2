#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

#define BASE_SIZE 2

template<class T, class K>
class HashMap {
public:
  HashMap(int(*hash)(const T &), bool(*keyCompare)(const T &, const T &)) : currentSize(0), maxCapacity(BASE_SIZE),
                                                                            hash(hash), keyCompare(keyCompare) {
    keys = new vector<list<pair<T, K> > >();
    keys->resize(BASE_SIZE);
  }
  ~HashMap() {
    delete keys;
  }
  bool add(const T &key, K value) {
    int index = getHashIndex(key);
    if (getOnIndex(index, key) != nullptr) {
      return false;
    }
    (*keys)[index].push_back(pair<T, K>(key, value));
    currentSize++;
    if (shouldResize()) {
      increaseCapacity();
    }
    return true;
  }
  bool remove(const T &key) {
    int index = getHashIndex(key);
    for (auto it = (*keys)[index].begin(); it != (*keys)[index].end(); it++) {
      if (keyCompare(it->first, key)) {
        (*keys)[index].erase(it);
        currentSize--;
        return true;
      }
    }
    return false;
  }
  bool contains(const T &key) const {
    const int index = getHashIndex(key);
    return getOnIndex(index, key) != nullptr;
  }
  K *get(const T &key) const {
    int index = getHashIndex(key);
    return getOnIndex(index, key);
  }
private:
  vector<list<pair<T, K> > > *keys;
  int currentSize;
  int maxCapacity;
  int (*hash)(const T &);
  bool (*keyCompare)(const T &, const T &);
  int getHashIndex(const T &key) const {
    return abs(hash(key)) % maxCapacity;
  }
  K *getOnIndex(int index, const T &key) const {
    for (auto it = (*keys)[index].begin(); it != (*keys)[index].end(); it++) {
      if (keyCompare(it->first, key)) {
        return &(it->second);
      }
    }
    return nullptr;
  }
  bool shouldResize() const {
    // 75% of max capacity (better than multiplying 0.75)
    return currentSize * 4 > maxCapacity * 3;
  }
  void increaseCapacity() {
    int newCapacity = maxCapacity * 2;
    auto *newKeys = new vector<list<pair<T, K> > >();
    newKeys->resize(newCapacity);
    for (int i = 0; i < maxCapacity; i++) {
      for (auto it = (*keys)[i].begin(); it != (*keys)[i].end(); it++) {
        int newIndex = abs(hash(it->first)) % newCapacity;
        (*newKeys)[newIndex].push_back(pair<T, K>(it->first, it->second));
      }
    }
    delete keys;
    keys = newKeys;
    maxCapacity = newCapacity;
  }
};

int hashString(const string &str) {
  int result = 0;
  for (size_t i = 0; i < str.length(); i++) {
    result = result * 31 + str[i];
  }
  return result;
}

bool compareStrings(const string &a, const string &b) {
  return a.compare(b) == 0;
}

class Person {
public:
  string name;
  string surname;
  string email;
  int salary;
  Person(const string &name, const string &surname, const string &email, const unsigned int salary) :
          name(name), surname(surname), email(email), salary(salary) {}
  ~Person() {}
  int compareByName(const Person *other) const {
    int result = this->surname.compare(other->surname);
    if (result != 0) {
      return result;
    } else {
      return this->name.compare(other->name);
    }
  }
  static bool isLowerByName(const Person *a, const Person *b) {
    return (*a).compareByName(b) < 0;
  }
  static bool isSameByName(const Person *a, const Person *b) {
    return (*a).compareByName(b) == 0;
  }
  static Person createDummy(const string &name, const string &surname) {
    return Person(name, surname, "", 0);
  }
};

class CPersonalAgenda {
public:
  CPersonalAgenda() : peopleByEmail(hashString, compareStrings) {}
  ~CPersonalAgenda() {
    for (auto it = peopleByName.begin(); it != peopleByName.end(); it++) {
      delete *it;
    }
  };
  bool add(const string &name,
          const string &surname,
          const string &email,
          unsigned int salary) {
    Person *target = new Person(name, surname, email, salary);
    auto foundItemPointer = lower_bound(this->peopleByName.begin(), this->peopleByName.end(), target,
            Person::isLowerByName);
    if (foundItemPointer != this->peopleByName.end() && Person::isSameByName(*foundItemPointer, target)) {
      delete target;
      return false;
    }
    if (peopleByEmail.contains(email)) {
      delete target;
      return false;
    }
    peopleByName.insert(foundItemPointer, target);
    peopleByEmail.add(email, target);
    return true;
  }

  bool del(const string &name,
          const string &surname) {
    int index = indexOf(name, surname);
    if (index == -1) {
      return false;
    }
    Person *person = peopleByName[index];
    peopleByEmail.remove(person->email);
    peopleByName.erase(peopleByName.begin() + index);
    delete person;
    return true;
  }

  bool del(const string &email) {
    Person **person = peopleByEmail.get(email);
    if (person == nullptr) {
      return false;
    }
    int index = indexOf((*person)->name, (*person)->surname);
    Person *personToErase = peopleByName[index];
    peopleByEmail.remove(email);
    peopleByName.erase(peopleByName.begin() + index);
    delete personToErase;
    return true;
  }

  bool changeName(const string &email,
          const string &newName,
          const string &newSurname) {
    Person **ref = peopleByEmail.get(email);
    if (ref == nullptr) {
      return false;
    }
    int index = indexOf((*ref)->name, (*ref)->surname);
    if (index == -1) {
      return false;
    }
    int salary = (*ref)->salary;
    Person target(newName, newSurname, email, salary);
    auto foundItemPointer = lower_bound(this->peopleByName.begin(), this->peopleByName.end(), &target,
            Person::isLowerByName);
    if (foundItemPointer != this->peopleByName.end() && Person::isSameByName(*foundItemPointer, &target)) {
      // new already exists
      return false;
    }
    delete peopleByName[index];
    peopleByEmail.remove(email);
    peopleByName.erase(peopleByName.begin() + index);
    this->add(newName, newSurname, email, salary);
    return true;
  }

  bool changeEmail(const string &name,
          const string &surname,
          const string &newEmail) {
    int index = indexOf(name, surname);
    if (index == -1) {
      return false;
    }
    bool existsNewEmail = peopleByEmail.contains(newEmail);
    if (existsNewEmail) {
      return false;
    }
    peopleByEmail.remove(peopleByName[index]->email);
    peopleByName[index]->email = newEmail;
    peopleByEmail.add(newEmail, peopleByName[index]);
    return true;
  }

  bool setSalary(const string &name,
          const string &surname,
          unsigned int salary) {
    int index = indexOf(name, surname);
    if (index == -1) {
      return false;
    }
    peopleByName[index]->salary = salary;
    return true;
  }

  bool setSalary(const string &email,
          unsigned int salary) {
    Person **ref = peopleByEmail.get(email);
    if (ref == nullptr) {
      return false;
    }
    (*ref)->salary = salary;
    return true;
  }

  unsigned int getSalary(const string &name,
          const string &surname) const {
    int index = indexOf(name, surname);
    if (index == -1) {
      return 0;
    }
    return peopleByName[index]->salary;
  }

  unsigned int getSalary(const string &email) const {
    Person **ref = peopleByEmail.get(email);
    if (ref == nullptr) {
      return 0;
    }
    return (*ref)->salary;
  }

  bool getRank(const string &name,
          const string &surname,
          int &rankMin,
          int &rankMax) const {
    int strictlyLowerCount = 0;
    int equalCount = 0;
    int salary = getSalary(name, surname);
    if(salary == 0) {
      return false;
    }
    for(size_t i = 0; i < peopleByName.size(); i++) {
      if(peopleByName[i]->salary < salary) {
        strictlyLowerCount++;
      } else if(peopleByName[i]->salary == salary) {
        equalCount++;
      }
    }
    rankMin = strictlyLowerCount;
    rankMax = strictlyLowerCount + equalCount - 1;
    return true;
  }

  bool getRank(const string &email,
          int &rankMin,
          int &rankMax) const {
    Person **ref = peopleByEmail.get(email);
    if (ref == nullptr) {
      return false;
    }
    return getRank((*ref)->name, (*ref)->surname, rankMin, rankMax);
  }

  bool getFirst(string &outName,
          string &outSurname) const {
    if (peopleByName.empty()) {
      return false;
    }
    outName = peopleByName[0]->name;
    outSurname = peopleByName[0]->surname;
    return true;
  }

  bool getNext(const string &name,
          const string &surname,
          string &outName,
          string &outSurname) const {
    int index = indexOf(name, surname);
    if (index == -1 || (size_t) index == peopleByName.size() - 1) {
      return false;
    }
    outName = peopleByName[index + 1]->name;
    outSurname = peopleByName[index + 1]->surname;
    return true;
  }
private:
  vector<Person *> peopleByName;
  HashMap<string, Person *> peopleByEmail;
  int indexOf(const string &name, const string &surname) const {
    Person target = Person::createDummy(name, surname);
    auto foundItemPointer = lower_bound(this->peopleByName.begin(), this->peopleByName.end(), &target,
            Person::isLowerByName);
    if (foundItemPointer == peopleByName.end() || !Person::isSameByName(*foundItemPointer, &target)) {
      return -1;
    }
    return foundItemPointer - peopleByName.begin();
  }
};

#ifndef __PROGTEST__
int main() {
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert (b1.add("John", "Smith", "john", 30000));
  assert (b1.add("John", "Miller", "johnm", 35000));
  assert (b1.add("Peter", "Smith", "peter", 23000));
  assert (b1.getFirst(outName, outSurname)
          && outName == "John"
          && outSurname == "Miller");
  assert (b1.getNext("John", "Miller", outName, outSurname)
          && outName == "John"
          && outSurname == "Smith");
  assert (b1.getNext("John", "Smith", outName, outSurname)
          && outName == "Peter"
          && outSurname == "Smith");
  assert (!b1.getNext("Peter", "Smith", outName, outSurname));
  assert (b1.setSalary("john", 32000));
  assert (b1.getSalary("john") == 32000);
  assert (b1.getSalary("John", "Smith") == 32000);
  assert (b1.getRank("John", "Smith", lo, hi)
          && lo == 1
          && hi == 1);
  assert (b1.getRank("john", lo, hi)
          && lo == 1
          && hi == 1);
  assert (b1.getRank("peter", lo, hi)
          && lo == 0
          && hi == 0);
  assert (b1.getRank("johnm", lo, hi)
          && lo == 2
          && hi == 2);
  assert (b1.setSalary("John", "Smith", 35000));
  assert (b1.getSalary("John", "Smith") == 35000);
  assert (b1.getSalary("john") == 35000);
  assert (b1.getRank("John", "Smith", lo, hi)
          && lo == 1
          && hi == 2);
  assert (b1.getRank("john", lo, hi)
          && lo == 1
          && hi == 2);
  assert (b1.getRank("peter", lo, hi)
          && lo == 0
          && hi == 0);
  assert (b1.getRank("johnm", lo, hi)
          && lo == 1
          && hi == 2);
  assert (b1.changeName("peter", "James", "Bond"));
  assert (b1.getSalary("peter") == 23000);
  assert (b1.getSalary("James", "Bond") == 23000);
  assert (b1.getSalary("Peter", "Smith") == 0);
  assert (b1.getFirst(outName, outSurname)
          && outName == "James"
          && outSurname == "Bond");
  assert (b1.getNext("James", "Bond", outName, outSurname)
          && outName == "John"
          && outSurname == "Miller");
  assert (b1.getNext("John", "Miller", outName, outSurname)
          && outName == "John"
          && outSurname == "Smith");
  assert (!b1.getNext("John", "Smith", outName, outSurname));
  assert (b1.changeEmail("James", "Bond", "james"));
  assert (b1.getSalary("James", "Bond") == 23000);
  assert (b1.getSalary("james") == 23000);
  assert (b1.getSalary("peter") == 0);
  assert (b1.del("james"));
  assert (b1.getRank("john", lo, hi)
          && lo == 0
          && hi == 1);
  assert (b1.del("John", "Miller"));
  assert (b1.getRank("john", lo, hi)
          && lo == 0
          && hi == 0);
  assert (b1.getFirst(outName, outSurname)
          && outName == "John"
          && outSurname == "Smith");
  assert (!b1.getNext("John", "Smith", outName, outSurname));
  assert (b1.del("john"));
  assert (!b1.getFirst(outName, outSurname));
  assert (b1.add("John", "Smith", "john", 31000));
  assert (b1.add("john", "Smith", "joHn", 31000));
  assert (b1.add("John", "smith", "jOhn", 31000));

  CPersonalAgenda b2;
  assert(!b2.getRank("james", lo, hi));
  assert(!b2.getSalary("james"));
  assert(!b2.setSalary("james", 10000));
  assert(!b2.changeName("james", "James", "Bond"));
  assert(!b2.changeEmail("James", "Bond", "james"));
  assert(!b2.del("james"));
  assert(!b2.getFirst(outName, outSurname));
  assert(!b2.getNext("James", "Bond", outName, outSurname));
  assert (!b2.getFirst(outName, outSurname));
  assert (b2.add("James", "Bond", "james", 70000));
  assert (b2.add("James", "Smith", "james2", 30000));
  assert (b2.add("Peter", "Smith", "peter", 40000));
  assert (!b2.add("James", "Bond", "james3", 60000));
  assert (!b2.add("Peter", "Bond", "peter", 50000));
  assert (b2.add("", "", "", 50000));
  assert (!b2.add("", "", "", 0));
  assert (!b2.changeName("joe", "Joe", "Black"));
//  assert (!b2.setSalary("Joe", "Black", 90000));
//  assert (!b2.setSalary("joe", 90000));
//  assert (b2.getSalary("Joe", "Black") == 0);
//  assert (b2.getSalary("joe") == 0);
//  assert (!b2.getRank("Joe", "Black", lo, hi));
//  assert (!b2.getRank("joe", lo, hi));
//  assert (!b2.changeName("joe", "Joe", "Black"));
//  assert (!b2.changeEmail("Joe", "Black", "joe"));
//  assert (!b2.del("Joe", "Black"));
//  assert (!b2.del("joe"));
//  assert (!b2.changeName("james2", "James", "Bond"));
//  assert (!b2.changeEmail("Peter", "Smith", "james"));
//  assert (!b2.changeName("peter", "Peter", "Smith"));
//  assert (!b2.changeEmail("Peter", "Smith", "peter"));
//  assert (b2.del("Peter", "Smith"));
//  assert (!b2.changeEmail("Peter", "Smith", "peter2"));
//  assert (!b2.setSalary("Peter", "Smith", 35000));
//  assert (b2.getSalary("Peter", "Smith") == 0);
//  assert (!b2.getRank("Peter", "Smith", lo, hi));
//  assert (!b2.changeName("peter", "Peter", "Falcon"));
//  assert (!b2.setSalary("peter", 37000));
//  assert (b2.getSalary("peter") == 0);
//  assert (!b2.getRank("peter", lo, hi));
//  assert (!b2.del("Peter", "Smith"));
//  assert (!b2.del("peter"));
//  assert (b2.add("Peter", "Smith", "peter", 40000));
//  assert (b2.getSalary("peter") == 40000);

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
