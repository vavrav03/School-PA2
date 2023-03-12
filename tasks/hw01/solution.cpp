#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#endif /* __PROGTEST__ */

#ifndef __PROGTEST__
const int BUFFER_SIZE = 4096;

bool identicalFiles(const char *file1, const char *file2) {
  ifstream f1(file1, ios::binary | ios::ate);
  ifstream f2(file2, ios::binary | ios::ate);
  if (f1.fail() || f2.fail() || f1.tellg() != f2.tellg()) {
    return false;
  }
  f1.seekg(0, ios::beg);
  f2.seekg(0, ios::beg);
  char buffer1[BUFFER_SIZE];
  char buffer2[BUFFER_SIZE];
  while (f1.good() && f2.good()) {
    f1.read(buffer1, BUFFER_SIZE);
    f2.read(buffer2, BUFFER_SIZE);
    if (f1.gcount() != f2.gcount() || memcmp(buffer1, buffer2, f1.gcount()) != 0) {
      return false;
    }
  }
  if (!f1.eof() || !f2.eof()) {
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  ifstream f1("example/dst_0.fib", ios::binary);
  assert(identicalFiles("example/dst_0.fib", "example/dst_0.fib"));
  assert(!identicalFiles("example/dst_0.fib", "example/dst_1.fib"));
  assert(utf8ToFibonacci("example/src_0.utf8", "output.fib") && identicalFiles("output.fib", "example/dst_0.fib"));
  assert(utf8ToFibonacci("example/src_1.utf8", "output.fib") && identicalFiles("output.fib", "example/dst_1.fib"));
  assert(utf8ToFibonacci("example/src_2.utf8", "output.fib") && identicalFiles("output.fib", "example/dst_2.fib"));
  assert(utf8ToFibonacci("example/src_3.utf8", "output.fib") && identicalFiles("output.fib", "example/dst_3.fib"));
  assert(utf8ToFibonacci("example/src_4.utf8", "output.fib") && identicalFiles("output.fib", "example/dst_4.fib"));
  assert(!utf8ToFibonacci("example/src_5.utf8", "output.fib"));
  assert(fibonacciToUtf8("example/src_6.fib", "output.utf8") && identicalFiles("output.utf8", "example/dst_6.utf8"));
  assert(fibonacciToUtf8("example/src_7.fib", "output.utf8") && identicalFiles("output.utf8", "example/dst_7.utf8"));
  assert(fibonacciToUtf8("example/src_8.fib", "output.utf8") && identicalFiles("output.utf8", "example/dst_8.utf8"));
  assert(fibonacciToUtf8("example/src_9.fib", "output.utf8") && identicalFiles("output.utf8", "example/dst_9.utf8"));
  assert(fibonacciToUtf8("example/src_10.fib", "output.utf8") &&
          identicalFiles("output.utf8", "example/dst_10.utf8"));
  assert(!fibonacciToUtf8("example/src_11.fib", "output.utf8"));

  return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
