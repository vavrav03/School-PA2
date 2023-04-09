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

void toLowerCase(string &str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void squeezeCharacters(string &str, char c) {
  str.erase(unique(str.begin(), str.end(), [](char a, char b) { return a == ' ' && b == ' '; }), str.end());
}

void squeezeSpaces(string &str) {
  squeezeCharacters(str, ' ');
}

void removeLeadingSpaces(string &str) {
  str.erase(str.begin(), find_if(str.begin(), str.end(), [](char ch) { return !isspace(ch); }));
}

void removeTrailingSpaces(string &str) {
  str.erase(find_if(str.rbegin(), str.rend(), [](char ch) { return !isspace(ch); }).base(), str.end());
}

class CInvoice {
public:
  CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat)
          : m_Date(date), m_Buyer(buyer), m_Seller(seller), m_Amount(amount), m_Vat(vat) {}
  CDate date(void) const { return m_Date; }
  string buyer(void) const { return m_Buyer; }
  string seller(void) const { return m_Seller; }
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
      size_t buyerHash = hash<string>()(x.m_Buyer);
      size_t sellerHash = hash<string>()(x.m_Seller);
      size_t amountHash = hash<unsigned int>()(x.m_Amount);
      size_t vatHash = hash<double>()(x.m_Vat);
      return dateHash ^ buyerHash ^ sellerHash ^ amountHash ^ vatHash;
    }
  };

private:
  CDate m_Date;
  string m_Buyer;
  string m_Seller;
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

int compareCaseInsensitive(const string &a, const string &b) {
  string aCopy = a;
  string bCopy = b;
  toLowerCase(aCopy);
  toLowerCase(bCopy);
  return aCopy.compare(bCopy);
}

class CompanyDatabase {
public:
  CompanyDatabase(void) : translatedCompaniesToOriginal() {}
  bool registerCompany(const string &name) {
    string transformedName = createTransformedName(name);
    return translatedCompaniesToOriginal.insert(make_pair(transformedName, name)).second;
  }
  bool existsCompany(const string &name) const {
    return translatedCompaniesToOriginal.find(name) != translatedCompaniesToOriginal.end();
  }
  bool existCompanies(const CInvoice &invoice) const {
    return existsCompany(invoice.buyer()) && existsCompany(invoice.seller());
  }
  static CInvoice createtInvoice(const CInvoice &invoice) {
    string transformedBuyer = createTransformedName(invoice.buyer());
    string transformedSeller = createTransformedName(invoice.seller());
    return CInvoice(invoice.date(), transformedSeller, transformedBuyer, invoice.amount(), invoice.vat());
  }
  /**
   * @brief This function presumes that there are original names of companies in the database.
   * @param invoice Invoice with transformed names of companies.
   * @return Invoice with original names of companies.
   */
  CInvoice createInvoiceWithOriginalNames(const CInvoice &invoice) {
    string originalBuyer = getOriginalName(invoice.buyer());
    string originalSeller = getOriginalName(invoice.seller());
    return CInvoice(invoice.date(), originalSeller, originalBuyer, invoice.amount(), invoice.vat());
  }
  static string createTransformedName(const string &name) {
    string transformedName = name;
    squeezeSpaces(transformedName);
    removeLeadingSpaces(transformedName);
    removeTrailingSpaces(transformedName);
    toLowerCase(transformedName);
    return transformedName;
  }
private:
  unordered_map<string, string> translatedCompaniesToOriginal;

  string getOriginalName(const string &name) const {
    return translatedCompaniesToOriginal.find(name)->second;
  }
};

class CVATRegister {
public:
  CVATRegister(void) {}
  bool registerCompany(const string &name) {
    return companies.registerCompany(name);
  }
  bool addIssued(const CInvoice &x) {
    CInvoice tInvoice = CompanyDatabase::createtInvoice(x);
    if (!companies.existCompanies(tInvoice) || isInvoiceIssued(tInvoice) ||
            tInvoice.hasSameSellerAndBuyer()) {
      return false;
    }
    issuedInvoices[tInvoice.seller()].insert(tInvoice);
    return true;
  }
  bool addAccepted(const CInvoice &x) {
    CInvoice tInvoice = CompanyDatabase::createtInvoice(x);
    if (!companies.existCompanies(tInvoice) || isInvoiceAccepted(tInvoice) ||
            tInvoice.hasSameSellerAndBuyer()) {
      return false;
    }
    acceptedInvoices[tInvoice.seller()].insert(tInvoice);
    return true;
  }
  bool delIssued(const CInvoice &x) {
    CInvoice tInvoice = CompanyDatabase::createtInvoice(tInvoice);
    if (!companies.existCompanies(tInvoice) || !isInvoiceIssued(tInvoice)) {
      return false;
    }
    issuedInvoices[tInvoice.seller()].erase(tInvoice);
    return true;
  }
  bool delAccepted(const CInvoice &x) {
    CInvoice tInvoice = CompanyDatabase::createtInvoice(x);
    if (!companies.existCompanies(tInvoice) || !isInvoiceAccepted(tInvoice)) {
      return false;
    }
    acceptedInvoices[tInvoice.seller()].erase(tInvoice);
    return true;
  }
  list<CInvoice> unmatched(const string &companyName, const CSortOpt &sortBy) const {
    string company(companyName);
    list<CInvoice> result;
    return result;
  }
private:
  CompanyDatabase companies;
  unordered_map<string, unordered_set<CInvoice, CInvoice::Hash>, hash<string>> issuedInvoices;
  unordered_map<string, unordered_set<CInvoice, CInvoice::Hash>, hash<string>> acceptedInvoices;
  bool isInvoiceIssued(const CInvoice &invoice) const {
    return existsInvoiceRecord(invoice, issuedInvoices);
  }
  bool isInvoiceAccepted(const CInvoice &invoice) const {
    return existsInvoiceRecord(invoice, acceptedInvoices);
  }
  bool existsInvoiceRecord(const CInvoice &invoice,
          const unordered_map<string, unordered_set<CInvoice, CInvoice::Hash>, hash<string>> &invoices) const {
    auto invoicesForSeller = invoices.find(invoice.seller());
    if (invoicesForSeller == invoices.end()) {
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
