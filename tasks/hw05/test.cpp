#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>

using namespace std;

class CDate {
public:
  CDate(int y, int m, int d) : m_Year(y), m_Month(m), m_Day(d) {
  }
  int compare(const CDate &x) const {
    if (m_Year != x.m_Year)
      return m_Year - x.m_Year;
    if (m_Month != x.m_Month)
      return m_Month - x.m_Month;
    return m_Day - x.m_Day;
  }
  int year(void) const {
    return m_Year;
  }
  int month(void) const {
    return m_Month;
  }
  int day(void) const {
    return m_Day;
  }
  friend ostream &operator<<(ostream &os, const CDate &x) {
    char oldFill = os.fill();
    return os << setfill('0') << setw(4) << x.m_Year << "-" << setw(2) << static_cast<int> ( x.m_Month ) << "-"
            << setw(2) << static_cast<int> ( x.m_Day ) << setfill(oldFill);
  }
private:
  int16_t m_Year;
  int8_t m_Month;
  int8_t m_Day;
};

#endif /* __PROGTEST__ */

class CInvoice {
public:
  CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat) {}
  CDate date(void) const { return CDate(0, 0, 0); }
  string buyer(void) const { return ""; }
  string seller(void) const { return ""; }
  unsigned int amount(void) const { return 0; }
  double vat(void) const { return 0; }
private:
  // todo

};

class CSortOpt {
public:
  static const int BY_DATE = 0;
  static const int BY_BUYER = 1;
  static const int BY_SELLER = 2;
  static const int BY_AMOUNT = 3;
  static const int BY_VAT = 4;
  CSortOpt(void) {}
  CSortOpt &addKey(int key, bool ascending = true) {
    return *this;
  }
private:
  // todo
};

class Company {
public:
  explicit Company(const string &name) : name(name), transformedName(Company::createTransformedString(name)) {}

  string getName() const { return name; }

  bool operator==(const Company &x) const {
    return (this->transformedName) == x.transformedName;
  }

  struct Hash {
    size_t operator()(const Company &x) const {
      return hash<string>()(x.transformedName);
    }
  };

  static string createTransformedString(const string &name) {
    string result = name;
    // squeeze spaces (last result.end() is pertinent to erase method, not unique)
    result.erase(unique(result.begin(), result.end(), [](char a, char b) { return a == ' ' && b == ' '; }),
            result.end());
    // remove leading and trailing spaces
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](char ch) { return !isspace(ch); }));
    result.erase(find_if(result.rbegin(), result.rend(), [](char ch) { return !isspace(ch); }).base(), result.end());
    // transform to lower case
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    cout << result << endl;
    return result;
  }

private:
  string name;
  string transformedName;
};

class CVATRegister {
public:
  CVATRegister(void) {}
  bool registerCompany(const string &name) {
    return companies.insert(Company(name)).second;
  }
  bool addIssued(const CInvoice &x) { return false; }
  bool addAccepted(const CInvoice &x) { return false; }
  bool delIssued(const CInvoice &x) { return false; }
  bool delAccepted(const CInvoice &x) { return false; }
  list<CInvoice> unmatched(const string &company, const CSortOpt &sortBy) const {
    return list<CInvoice>();
  }
private:
  unordered_set<Company, Company::Hash> companies;
};

#ifndef __PROGTEST__
bool equalLists(const list<CInvoice> &a, const list<CInvoice> &b) {
  // todo
  return false;
}

int main(void) {
  CVATRegister r;
  assert (r.registerCompany("first Company"));
  assert (r.registerCompany("Second     Company"));
  assert (r.registerCompany("ThirdCompany, Ltd."));
  assert (r.registerCompany("Third Company, Ltd."));
  assert (!r.registerCompany("Third Company, Ltd."));
  assert (!r.registerCompany(" Third  Company,  Ltd.  "));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
  assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
  assert (!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
  assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, false).addKey(CSortOpt::BY_DATE,
                          false)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER,
                          true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000)}));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(CSortOpt::BY_DATE,
                          true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert (equalLists(r.unmatched("First Company", CSortOpt()),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));
  assert (equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400, 34.000000)}));
  assert (equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)), list<CInvoice>{}));
  assert (r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
  assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE,
                          true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert (!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
  assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
  assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
  assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
  assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
  assert (r.delIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE,
                          true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert (r.delAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE,
                          true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert (r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert (equalLists(r.unmatched("First Company",
                  CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE,
                          true)),
          list<CInvoice>{CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                         CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
