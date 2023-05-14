#include "./console.h"
#include <iostream>

using namespace std;

ConsoleInterface::ConsoleInterface(): AbstractInterface()
{
}

void ConsoleInterface::run()
{
  cout << "Welcome to the console interface!" << endl;
}