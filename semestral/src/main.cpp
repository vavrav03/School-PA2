#include <iostream>

/**
 * @brief This is a dummy class
 */
class AnotherClass {
};

/**
 * This class should appear in documentation
 */
class DummyClassForDocTest : public AnotherClass {
public:
  /**
   * @brief This is a dummy method
   */
  DummyClassForDocTest() = default;

  void hello() {
    std::cout << "Hello, World!" << std::endl;

  }
};


/**
 * @brief This is an entry point to the program.
 * @return
 */
int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
