#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

/**
 * Representation of an adjacency list from graph theory using unordered_maps.
 * @tparam M_ generic class representing result type of a match between contestant1 and contestant2
 */
template<typename M_>
class MatchResultsDatabase {
public:

  MatchResultsDatabase() = default;

  /**
   * This method assumes that contestant1 and contestant2 are not the same string.
   * Runs in O(1) time.
   * @param contestant1
   * @param contestant2
   * @param result
   * @throws logic_error if contestant1 and contestant2 have already played against each other and the result is stored here
   */
  void addRecord(const string &contestant1, const string &contestant2, const M_ &result) {
    if (existsRecord(contestant1, contestant2)) {
      throw logic_error("Record already exists");
    }
    auto &againstValues = keyAgainstValues[contestant1];
    againstValues.insert(make_pair(contestant2, result));
  }

private:

  /**
   * Runs in O(1) time.
   * @param contestant1
   * @param contestant2
   * @return true, if contestants have already played against each other and the result is stored here
   */
  bool existsRecord(const string &contestant1, const string &contestant2) {
    return existsRecordInMap(contestant1, contestant2) || existsRecordInMap(contestant2, contestant1);
  }

  /**
   * This method is dependent on the order of parameters
   * @param contestant1
   * @param contestant2
   * @return true, if contestants have already played against each other and the result is stored here
   */
  bool existsRecordInMap(const string &contestant1, const string &contestant2) {
    if (keyAgainstValues.find(contestant1) == keyAgainstValues.end()) {
      return false;
    }
    if (keyAgainstValues[contestant1].find(contestant2) == keyAgainstValues[contestant1].end()) {
      return false;
    }
    return true;
  }

  // key is first contestant from add method. There is no way knowing what does M_ actually mean
  // and there is no way of knowing how to make and inverse record for second contestant,
  // therefore same record is NOT present for the second contestant in this map!
  unordered_map<string, unordered_map<string, M_, hash<string>>, hash<string>> keyAgainstValues;
};

template<typename M_>
class CContest {
public:

  CContest() = default;

  CContest &addMatch(const string &contestant1, const string &contestant2, const M_ &result) {
    matchResults.addRecord(contestant1, contestant2, result);
    return *this;
  }

  bool isOrdered(function<int(const M_ &)> compareFunc) {
    return false;
  }

  list<string> results(function<int(const M_ &)> compareFunc) {
    return list<string>();
  }

private:
  MatchResultsDatabase<M_> matchResults;
};

#ifndef __PROGTEST__

struct CMatch {
public:
  CMatch(int a, int b) : m_A(a), m_B(b) {
  }

  int m_A;
  int m_B;
};

class HigherScoreThreshold {
public:
  HigherScoreThreshold(int diffAtLeast) : m_DiffAtLeast(diffAtLeast) {
  }

  int operator()(const CMatch &x) const {
    return (x.m_A > x.m_B + m_DiffAtLeast) - (x.m_B > x.m_A + m_DiffAtLeast);
  }

private:
  int m_DiffAtLeast;
};

int HigherScore(const CMatch &x) {
  return (x.m_A > x.m_B) - (x.m_B > x.m_A);
}

int main(void) {
  CContest<CMatch> x;

  x.addMatch("C++", "Pascal", CMatch(10, 3))
          .addMatch("C++", "Java", CMatch(8, 1))
          .addMatch("Pascal", "Basic", CMatch(40, 0))
          .addMatch("Java", "PHP", CMatch(6, 2))
          .addMatch("Java", "Pascal", CMatch(7, 3))
          .addMatch("PHP", "Basic", CMatch(10, 0));

  try {
    x.addMatch("PHP", "Basic", CMatch(0, 10));
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }


  assert (!x.isOrdered(HigherScore));
  try {
    list<string> res = x.results(HigherScore);
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }

  x.addMatch("PHP", "Pascal", CMatch(3, 6));

  assert (x.isOrdered(HigherScore));
  try {
    list<string> res = x.results(HigherScore);
    assert ((res == list<string>{"C++", "Java", "Pascal", "PHP", "Basic"}));
  } catch (...) {
    assert ("Unexpected exception!" == nullptr);
  }


  assert (!x.isOrdered(HigherScoreThreshold(3)));
  try {
    list<string> res = x.results(HigherScoreThreshold(3));
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }

  assert (x.isOrdered([](const CMatch &x) {
    return (x.m_A < x.m_B) - (x.m_B < x.m_A);
  }));
  try {
    list<string> res = x.results([](const CMatch &x) {
      return (x.m_A < x.m_B) - (x.m_B < x.m_A);
    });
    assert ((res == list<string>{"Basic", "PHP", "Pascal", "Java", "C++"}));
  } catch (...) {
    assert ("Unexpected exception!" == nullptr);
  }

  CContest<bool> y;

  y.addMatch("Python", "PHP", true)
          .addMatch("PHP", "Perl", true)
          .addMatch("Perl", "Bash", true)
          .addMatch("Bash", "JavaScript", true)
          .addMatch("JavaScript", "VBScript", true);

  assert (y.isOrdered([](bool v) {
    return v ? 10 : -10;
  }));
  try {
    list<string> res = y.results([](bool v) {
      return v ? 10 : -10;
    });
    assert ((res == list<string>{"Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript"}));
  } catch (...) {
    assert ("Unexpected exception!" == nullptr);
  }

  y.addMatch("PHP", "JavaScript", false);
  assert (!y.isOrdered([](bool v) {
    return v ? 10 : -10;
  }));
  try {
    list<string> res = y.results([](bool v) {
      return v ? 10 : -10;
    });
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }

  try {
    y.addMatch("PHP", "JavaScript", false);
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }

  try {
    y.addMatch("JavaScript", "PHP", true);
    assert ("Exception missing!" == nullptr);
  } catch (const logic_error &e) {
  } catch (...) {
    assert ("Invalid exception thrown!" == nullptr);
  }
  return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
