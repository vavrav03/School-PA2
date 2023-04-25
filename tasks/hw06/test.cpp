#ifndef __PROGTEST__

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class CRect {
public:
  CRect(double x, double y, double w, double h) : m_X(x), m_Y(y), m_W(w), m_H(h) {}

  friend ostream &operator<<(ostream &os, const CRect &x) {
    return os << '(' << x.m_X << ',' << x.m_Y << ',' << x.m_W << ',' << x.m_H << ')';
  }

  double m_X;
  double m_Y;
  double m_W;
  double m_H;
};

#endif /* __PROGTEST__ */

class Component {
public:
  Component(int id, const string &name, const CRect &relPos)
          : m_Id(id), m_Name(name), m_RelPos(relPos), m_AbsPos(-1, -1, -1, -1) {}

  void calculateAbsPos(const CRect &windowPos) {
    m_AbsPos = CRect(floor(windowPos.m_X + m_RelPos.m_X * windowPos.m_W),
            floor(windowPos.m_Y + m_RelPos.m_Y * windowPos.m_H),
            floor(m_RelPos.m_W * windowPos.m_W),
            floor(m_RelPos.m_H * windowPos.m_H));
  }

  int getID() const { return m_Id; }

  friend ostream &operator<<(ostream &o, const Component &comp) {
    return o << comp.toString(0, true);
  }

  virtual string toString(int indentLevel, bool isLast) const = 0;

  virtual Component *clone() const = 0;

  virtual ~Component() = default;

protected:
  int m_Id;
  string m_Name;
  CRect m_RelPos;
  CRect m_AbsPos;

  string idToString() const { return "[" + to_string(m_Id) + "] "; }

  string getPositionString() const {
    ostringstream oss;
    oss << m_AbsPos;
    return oss.str();
  }
};

class TitledComponent : public Component {
public:
  TitledComponent(int id, const string &name, const CRect &relPos, const string &title) : Component(id, name, relPos),
                                                                                          m_Title(title) {}

  string toString(int indentLevel, bool isLast) const override {
    return idToString() + m_Name + " \"" + m_Title + "\" " + getPositionString() + "\n";
  }

  TitledComponent *clone() const override {
    return new TitledComponent(m_Id, m_Name, m_RelPos, m_Title);
  }

protected:

  string m_Title;
};

class CWindow : public TitledComponent {
public:
  CWindow(int id, const string &title, const CRect &absPos) : TitledComponent(id, "Window", absPos, title) {
    m_AbsPos = absPos;
  }

  CWindow(const CWindow &window) : TitledComponent(window.m_Id, window.m_Name, window.m_RelPos, window.m_Title) {
    m_AbsPos = window.m_AbsPos;
    for (auto *component: window.m_Components) {
      add(*component);
    }
  }

  CWindow& operator=(const CWindow& other) {
    if (this != &other) {
      m_Id = other.m_Id;
      m_Name = other.m_Name;
      m_RelPos = other.m_RelPos;
      m_AbsPos = other.m_AbsPos;
      m_Title = other.m_Title;
      for (auto *component: m_Components) {
        delete component;
      }
      m_Components.clear();
      for (auto *component: other.m_Components) {
        add(*component);
      }
    }
    return *this;
  };

  CWindow &add(const Component &component) {
    Component *c = component.clone();
    m_Components.push_back(c);
    c->calculateAbsPos(m_RelPos);
    return *this;
  }

  Component *search(int id) const {
    for (Component *c: m_Components) {
      if (c->getID() == id) { return c; }
    }
    return nullptr;
  }

  string toString(int indentLevel, bool isLast) const override {
    string s = TitledComponent::toString(indentLevel, isLast);
    for (Component *component: m_Components) {
      if (indentLevel > 0) {
        s += isLast ? "   " : "|  ";
      }
      for (int i = 1; i < indentLevel; i++) s += "  ";
      s += "+- " + component->toString(indentLevel + 1, isLast && component == m_Components.back());
    }
    return s;
  }

  CWindow *clone() const override {
    CWindow *window = new CWindow(m_Id, m_Title, m_RelPos);
    for (auto *component: m_Components) {
      window->add(*component);
    }
    return window;
  }

  void setPosition(const CRect &absPos) {
    m_RelPos = absPos;
    m_AbsPos = absPos;
    for (auto *component: m_Components) {
      component->calculateAbsPos(absPos);
    }
  }

  ~CWindow() {
    for (auto *component: m_Components) {
      delete component;
    }
  }

private:
  vector<Component *> m_Components;
};

class CButton : public TitledComponent {
public:
  CButton(int id, const CRect &relPos, const string &name) : TitledComponent(id, "Button", relPos, name) {}

  CButton *clone() const override {
    return new CButton(m_Id, m_RelPos, m_Title);
  }
};

class CInput : public TitledComponent {
public:
  CInput(int id, const CRect &relPos, const string &value) : TitledComponent(id, "Input", relPos, value) {}

  void setValue(const string &value) { m_Title = value; }

  string &getValue() { return m_Title; }

  CInput *clone() const override {
    return new CInput(m_Id, m_RelPos, m_Title);
  }
};

class CLabel : public TitledComponent {
public:
  CLabel(int id, const CRect &relPos, const string &label) : TitledComponent(id, "Label", relPos, label) {}

  CLabel *clone() const override {
    return new CLabel(m_Id, m_RelPos, m_Title);
  }
};

class CComboBox : public Component {
public:
  CComboBox(int id, const CRect &relPos) : Component(id, "ComboBox", relPos), m_SelectedIndex(0) {}

  CComboBox &add(const string &item) {
    m_Items.push_back(item);
    return *this;
  }

  void setSelected(int selectedIndex) { m_SelectedIndex = selectedIndex; }

  int getSelected() { return m_SelectedIndex; }

  string toString(int indentLevel, bool isLast) const override {
    string s = idToString() + m_Name + " " + getPositionString() + "\n";
    for (size_t i = 0; i < m_Items.size(); i++) {
      if (indentLevel > 0) {
        s += isLast ? "   " : "|  ";
      }
      for (int j = 1; j < indentLevel; j++) s += "   ";
      if (i == m_SelectedIndex) { s += "+->" + m_Items[i] + "<"; }
      else { s += "+- " + m_Items[i]; }
      s += "\n";
    }
    return s;
  }

  CComboBox *clone() const override {
    CComboBox *comboBox = new CComboBox(m_Id, m_RelPos);
    for (auto &item: m_Items) {
      comboBox->add(item);
    }
    comboBox->setSelected(m_SelectedIndex);
    return comboBox;
  }

private:
  vector<string> m_Items;
  int m_SelectedIndex;
};

// output operators

#ifndef __PROGTEST__

template<typename T>
string toString(const T &x) {
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void) {
  assert(sizeof(CButton) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
  assert(sizeof(CInput) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
  assert(sizeof(CLabel) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
  CWindow a(0, "Sample window", CRect(10, 10, 600, 480));

  a.add(CButton(1, CRect(0.1, 0.8, 0.3, 0.1), "Ok")).add(CButton(2, CRect(0.6, 0.8, 0.3, 0.1), "Cancel"));
  a.add(CLabel(10, CRect(0.1, 0.1, 0.2, 0.1), "Username:"));
  a.add(CInput(11, CRect(0.4, 0.1, 0.5, 0.1), "chucknorris"));
  a.add(CComboBox(20, CRect(0.1, 0.3, 0.8, 0.1)).add("Karate").add("Judo").add("Box").add("Progtest"));
  assert(toString(a) == "[0] Window \"Sample window\" (10,10,600,480)\n"
                        "+- [1] Button \"Ok\" (70,394,180,48)\n"
                        "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                        "+- [10] Label \"Username:\" (70,58,120,48)\n"
                        "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
                        "+- [20] ComboBox (70,154,480,48)\n"
                        "   +->Karate<\n"
                        "   +- Judo\n"
                        "   +- Box\n"
                        "   +- Progtest\n");
  CWindow b = a;
  assert(toString(*b.search(20)) == "[20] ComboBox (70,154,480,48)\n"
                                    "+->Karate<\n"
                                    "+- Judo\n"
                                    "+- Box\n"
                                    "+- Progtest\n");
  assert(dynamic_cast<CComboBox &>(*b.search(20)).getSelected() == 0);
  dynamic_cast<CComboBox &>(*b.search(20)).setSelected(3);
  assert(toString(*b.search(20)) == "[20] ComboBox (70,154,480,48)\n"
                                    "+- Karate\n"
                                    "+- Judo\n"
                                    "+- Box\n"
                                    "+->Progtest<\n");
  assert(dynamic_cast<CInput &>(*b.search(11)).getValue() == "chucknorris");
  dynamic_cast<CInput &>(*b.search(11)).setValue("chucknorris@fit.cvut.cz");
  b.add(CComboBox(21, CRect(0.1, 0.5, 0.8, 0.1)).add("PA2").add("OSY").add("Both"));
  assert(toString(b) == "[0] Window \"Sample window\" (10,10,600,480)\n"
                        "+- [1] Button \"Ok\" (70,394,180,48)\n"
                        "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                        "+- [10] Label \"Username:\" (70,58,120,48)\n"
                        "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
                        "+- [20] ComboBox (70,154,480,48)\n"
                        "|  +- Karate\n"
                        "|  +- Judo\n"
                        "|  +- Box\n"
                        "|  +->Progtest<\n"
                        "+- [21] ComboBox (70,250,480,48)\n"
                        "   +->PA2<\n"
                        "   +- OSY\n"
                        "   +- Both\n");
  assert(toString(a) == "[0] Window \"Sample window\" (10,10,600,480)\n"
                        "+- [1] Button \"Ok\" (70,394,180,48)\n"
                        "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                        "+- [10] Label \"Username:\" (70,58,120,48)\n"
                        "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
                        "+- [20] ComboBox (70,154,480,48)\n"
                        "   +->Karate<\n"
                        "   +- Judo\n"
                        "   +- Box\n"
                        "   +- Progtest\n");
  b.setPosition(CRect(20, 30, 640, 520));
  assert(toString(b) == "[0] Window \"Sample window\" (20,30,640,520)\n"
                        "+- [1] Button \"Ok\" (84,446,192,52)\n"
                        "+- [2] Button \"Cancel\" (404,446,192,52)\n"
                        "+- [10] Label \"Username:\" (84,82,128,52)\n"
                        "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
                        "+- [20] ComboBox (84,186,512,52)\n"
                        "|  +- Karate\n"
                        "|  +- Judo\n"
                        "|  +- Box\n"
                        "|  +->Progtest<\n"
                        "+- [21] ComboBox (84,290,512,52)\n"
                        "   +->PA2<\n"
                        "   +- OSY\n"
                        "   +- Both\n");
  return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
