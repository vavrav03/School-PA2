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

    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
  }

private:
  string name;
  string transformedName;
};

class CInvoice {
public:
  CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat) : m_Date(
          date),
                                                                                                            m_Buyer(Company(
                                                                                                                    buyer)),
                                                                                                            m_Seller(
                                                                                                                    Company(
                                                                                                                            seller)),
                                                                                                            m_Amount(
                                                                                                                    amount),
                                                                                                            m_Vat(vat) {}
  CDate date(void) const { return m_Date; }
  string buyer(void) const { return m_Buyer.getName(); }
  string seller(void) const { return m_Seller.getName(); }
  Company buyerCompany(void) const { return m_Buyer; }
  Company sellerCompany(void) const { return m_Seller; }
  unsigned int amount(void) const { return m_Amount; }
  double vat(void) const { return m_Vat; }
  bool hasSameSellerAndBuyer(void) const {
    return m_Buyer == m_Seller;
  }

  bool operator==(const CInvoice &x) const {
    return this->date().compare(x.date()) == 0 && (this->m_Buyer == x.m_Buyer) && (this->m_Seller == x.m_Seller) &&
            (this->m_Amount == x.m_Amount) && (this->m_Vat == x.m_Vat);
  }

  struct Hash {
    size_t operator()(const CInvoice &x) const {
      size_t dateHash = hash<int>()(x.m_Date.year()) ^ hash<int>()(x.m_Date.month()) ^ hash<int>()(x.m_Date.day());
      size_t buyerHash = Company::Hash()(x.m_Buyer);
      size_t sellerHash = Company::Hash()(x.m_Seller);
      size_t amountHash = hash<unsigned int>()(x.m_Amount);
      size_t vatHash = hash<double>()(x.m_Vat);
      return dateHash ^ buyerHash ^ sellerHash ^ amountHash ^ vatHash;
    }
  };

private:
  CDate m_Date;
  Company m_Buyer;
  Company m_Seller;
  unsigned int m_Amount;
  double m_Vat;
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
    keys.push_back(make_pair(key, ascending));
    return *this;
  }
  bool operator()(const CInvoice &x, const CInvoice &y) const {
    for (auto key: keys) {
      switch (key.first) {
        case BY_DATE:
          if (x.date().compare(y.date()) != 0) {
            return key.second ? x.date().compare(y.date()) < 0 : x.date().compare(y.date()) > 0;
          }
          break;
        case BY_BUYER:
          if (x.buyer() != y.buyer()) {
            return key.second ? x.buyer() < y.buyer() : x.buyer() > y.buyer();
          }
          break;
        case BY_SELLER:
          if (x.seller() != y.seller()) {
            return key.second ? x.seller() < y.seller() : x.seller() > y.seller();
          }
          break;
        case BY_AMOUNT:
          if (x.amount() != y.amount()) {
            return key.second ? x.amount() < y.amount() : x.amount() > y.amount();
          }
          break;
        case BY_VAT:
          if (x.vat() != y.vat()) {
            return key.second ? x.vat() < y.vat() : x.vat() > y.vat();
          }
          break;
      }
    }
    return false;
  }
private:
  list<pair<int, bool>> keys;
};

class CVATRegister {
public:
  CVATRegister(void) {}
  bool registerCompany(const string &name) {
    return companies.insert(Company(name)).second;
  }
  bool addIssued(const CInvoice &x) {
    if (!existCompaniesFromInvoice(x) || isInvoiceIssued(x) || x.hasSameSellerAndBuyer()) {
      return false;
    }
    issuedInvoices[x.sellerCompany()].insert(x);
    return true;
  }
  bool addAccepted(const CInvoice &x) {
    if (!existCompaniesFromInvoice(x) || isInvoiceAccepted(x)|| x.hasSameSellerAndBuyer()) {
      return false;
    }
    acceptedInvoices[x.sellerCompany()].insert(x);
    return true;
  }
  bool delIssued(const CInvoice &x) {
    if (!existCompaniesFromInvoice(x) || !isInvoiceIssued(x)) {
      return false;
    }
    issuedInvoices[x.sellerCompany()].erase(x);
    return true;
  }
  bool delAccepted(const CInvoice &x) {
    // company does not have to be present in acceptedInvoices. Only after we check that company is present, can we check whether same invoice exists
    if (!existCompaniesFromInvoice(x) || !isInvoiceAccepted(x)) {
      return false;
    }
    acceptedInvoices[x.sellerCompany()].erase(x);
    return true;
  }
  list<CInvoice> unmatched(const string &companyName, const CSortOpt &sortBy) const {
    Company company(companyName);
    list<CInvoice> result;
    return result;
  }
private:
  unordered_set<Company, Company::Hash> companies;
  unordered_map<Company, unordered_set<CInvoice, CInvoice::Hash>, Company::Hash> issuedInvoices;
  unordered_map<Company, unordered_set<CInvoice, CInvoice::Hash>, Company::Hash> acceptedInvoices;
  bool isInvoiceIssued(const CInvoice &invoice) const {
    return existsInvoiceRecord(invoice, issuedInvoices);
  }
  bool isInvoiceAccepted(const CInvoice &invoice) const {
    return existsInvoiceRecord(invoice, acceptedInvoices);
  }
  bool existsCompany(const Company &company) const {
    return companies.find(company) != companies.end();
  }
  bool existCompaniesFromInvoice(const CInvoice &invoice) const {
    return existsCompany(invoice.buyerCompany()) && existsCompany(invoice.sellerCompany());
  }
  bool existsInvoiceRecord(const CInvoice &invoice,
          const unordered_map<Company, unordered_set<CInvoice, CInvoice::Hash>, Company::Hash> &invoices) const {
    auto invoicesForSeller = invoices.find(invoice.sellerCompany());
    if(invoicesForSeller == invoices.end()){
      return false;
    }
    return invoicesForSeller->second.find(invoice) != invoicesForSeller->second.end();
  }
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
