#ifndef __TESTING_MACRO_RELGEBRA__

#include "./module1/module1.cpp"

/**
 * @brief This is an entry point to the program.
 * @return
 */
int main() {
    method1();
    return 0;
}

#else // __TESTING_MACRO_RELGEBRA__

#include "./module1/module1.test.cpp"

int main() {
  testMain();
  return 0;
}

#endif // __TESTING_MACRO_RELGEBRA__
