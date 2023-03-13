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

#define WRONG_INPUT (-2)
#define END_OF_INPUT (-1)
#define FIBONACCI_NUMBERS_COUNT 30

class UTF8Stream {
public:
  explicit UTF8Stream(fstream &stream) : stream(stream) {};
  int readOneCodepoint();
  void writeOneCodepoint(int codepoint);
private:
  fstream &stream;
  static int getNextBytesCount(char byte);
  static bool isSuccessorByte(char byte);
  static int getCodePointBinaryLength(int codepoint);
};

int UTF8Stream::getNextBytesCount(char byte) {
  if ((byte & 0b10000000) == 0) {
    return 0;
  }
  if ((byte & 0b11100000) == 0b11000000) {
    return 1;
  }
  if ((byte & 0b11110000) == 0b11100000) {
    return 2;
  }
  if ((byte & 0b11111000) == 0b11110000) {
    return 3;
  }
  return -1;
}
bool UTF8Stream::isSuccessorByte(char byte) {
  return (byte & 0b11000000) == 0b10000000;
}
int UTF8Stream::readOneCodepoint() {
  char byte;
  stream.read(&byte, 1);
  if (stream.eof()) {
    return END_OF_INPUT;
  } else if (!stream.good()) {
    return WRONG_INPUT;
  }
  int nextBytesCount = getNextBytesCount(byte);
  if (nextBytesCount == -1) {
    return WRONG_INPUT;
  }
  if (nextBytesCount == 0) {
    return byte & 0b01111111;
  }
  int result = byte & (0b01111111 >> (nextBytesCount + 1));
  for (int i = 0; i < nextBytesCount; i++) {
    stream.read(&byte, 1);
    if (!stream.good()) { // more bytes were expected, but the stream ended
      return WRONG_INPUT;
    }
    if (!isSuccessorByte(byte)) {
      return WRONG_INPUT;
    }
    result = (result << 6) | (byte & 0b00111111); // most left bytes are the highest order bits (from leader byte)
  }
  if (result > 0x10FFFF) { // 0-0x10FFFF is the valid range for this task
    return WRONG_INPUT;
  }
  return result;
}
int UTF8Stream::getCodePointBinaryLength(int codepoint) {
  for (int i = 0; i <= 100; i++) {
    if ((codepoint >> i) == 0) {
      return i;
    }
  }
  return -1;
}
void UTF8Stream::writeOneCodepoint(int codepoint) {
  int length = getCodePointBinaryLength(codepoint);
  if (length <= 7) {
    char byte = codepoint;
    stream.write(&byte, 1);
  } else if (length <= 11) {
    char bytes[2];
    bytes[0] = 0b11000000 | (codepoint >> 6);
    bytes[1] = 0b10000000 | (codepoint & 0b00111111);
    stream.write(bytes, 2);
  } else if (length <= 16) {
    char bytes[3];
    bytes[0] = 0b11100000 | (codepoint >> 12);
    bytes[1] = 0b10000000 | ((codepoint >> 6) & 0b00111111);
    bytes[2] = 0b10000000 | (codepoint & 0b00111111);
    stream.write(bytes, 3);
  } else {
    char bytes[4];
    bytes[0] = 0b11110000 | (codepoint >> 18);
    bytes[1] = 0b10000000 | ((codepoint >> 12) & 0b00111111);
    bytes[2] = 0b10000000 | ((codepoint >> 6) & 0b00111111);
    bytes[3] = 0b10000000 | (codepoint & 0b00111111);
    stream.write(bytes, 4);
  }
}

class FibonacciSequence {
public:
  int sequence[FIBONACCI_NUMBERS_COUNT]{};
  FibonacciSequence() {
    sequence[0] = 1;
    sequence[1] = 2;
    for (int i = 2; i < FIBONACCI_NUMBERS_COUNT; i++) {
      sequence[i] = sequence[i - 1] + sequence[i - 2];
    }
  }
  int biggestLowerIndex(int number) {
    for (int i = FIBONACCI_NUMBERS_COUNT - 1; i >= 0; i--) {
      if (sequence[i] <= number) {
        return i;
      }
    }
    return -1;
  }
};

class FibonacciStream {
public:
  explicit FibonacciStream(fstream &stream) : stream(stream), fSeq(), bufferByte(0), bufferedCount(0) {}
  void writeOneCodepoint(int codepoint);
  int readOneCodepoint();
  void endOutput();
private:
  fstream &stream;
  FibonacciSequence fSeq;
  char bufferByte;
  int bufferedCount;
  void addToBuffer(int bit);
  int readNextBit();
  void readToBuffer();
};

void FibonacciStream::addToBuffer(int bit) {
  bufferByte |= (bit << bufferedCount);
  bufferedCount++;
  if (bufferedCount == 8) {
    stream.write(&bufferByte, 1);
    bufferedCount = 0;
    bufferByte = 0;
  }
}

void FibonacciStream::writeOneCodepoint(int codepoint) {
  codepoint++; // 0 is now 1
  int result = 0;
  int index = fSeq.biggestLowerIndex(codepoint); // should never be -1 here
  int biggestLowerIndex = index;
  while (index != -1) {
    result |= (1 << index);
    codepoint -= fSeq.sequence[index];
    index = fSeq.biggestLowerIndex(codepoint);
  }
  for (int i = 0; i <= biggestLowerIndex; i++) { // sending this to output from right to left (LSB is right)
    addToBuffer((result >> i) & 1);
  }
  addToBuffer(1);
}

void FibonacciStream::readToBuffer() {
  bufferedCount = 8;
  stream.read(&bufferByte, 1);
}

int FibonacciStream::readNextBit() { // read byte from right to left
  if (bufferedCount == 0) {
    readToBuffer();
  }
  int result = (bufferByte >> (8 - bufferedCount)) & 1;
  bufferedCount--;
  return result;
}

int FibonacciStream::readOneCodepoint() {
  bool onlyZeroes = true;
  if (stream.eof()) {
    return END_OF_INPUT;
  }
  int lastBit = readNextBit();
  int index = 0;
  int result;
  if (lastBit == 0) {
    result = 0;
  } else {
    onlyZeroes = false;
    result = fSeq.sequence[index];
  }
  int currentBit;
  while ((currentBit = readNextBit()) != 1 || lastBit != 1) {
    index++;
    lastBit = currentBit;
    if (stream.eof()) {
      return onlyZeroes ? END_OF_INPUT : WRONG_INPUT;
    }
    if (currentBit == 1) {
      onlyZeroes = false;
      result += fSeq.sequence[index];
    }
  }
  if(result - 1 > 0x10FFFF) {
    return WRONG_INPUT;
  }
  return result - 1;
}

void FibonacciStream::endOutput() {
  if (bufferedCount > 0) {
    stream.write(&bufferByte, 1);
    bufferedCount = 0;
    bufferByte = 0;
  }
}

bool utf8ToFibonacci(const char *inFile, const char *outFile) {
  fstream in(inFile, ios::in | ios::binary);
  fstream out(outFile, ios::out | ios::binary);
  if (!in.good() || !out.good()) {
    return false;
  }
  UTF8Stream utf8Stream(in);
  FibonacciStream fibonacciStream(out);
  int codepoint;
  while ((codepoint = utf8Stream.readOneCodepoint()) >= 0) {
    fibonacciStream.writeOneCodepoint(codepoint);
  }
  if(out.bad()){
    return false;
  }
  if (codepoint == END_OF_INPUT) {
    fibonacciStream.endOutput();
    return true;
  }
  return false;
}

bool fibonacciToUtf8(const char *inFile, const char *outFile) {
  fstream in(inFile, ios::in | ios::binary);
  fstream out(outFile, ios::out | ios::binary);
  if (!in.good() || !out.good()) {
    return false;
  }
  FibonacciStream fibonacciStream(in);
  UTF8Stream utf8Stream(out);
  int codepoint;
  while ((codepoint = fibonacciStream.readOneCodepoint()) >= 0) {
    utf8Stream.writeOneCodepoint(codepoint);
  }
  if(out.bad()){
    return false;
  }
  if (codepoint == END_OF_INPUT) {
    return true;
  }
  return false;
}

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
  fibonacciToUtf8("example/in_5025646.bin", "output.utf8");
  return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
