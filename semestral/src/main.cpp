
#include "./user-interfaces/abstract/abstract.h"
#include <string>
#include <iostream>

using namespace std;

string getValue(string name, int argc, char **argv)
{
  for (int i = 0; i < argc; i++)
  {
    if (string(argv[i]) == name)
    {
      if (i + 1 >= argc)
      {
        throw runtime_error("No value specified for" + name);
      }
      return string(argv[i + 1]);
    }
  }
  throw runtime_error("No flag " + name + " specified.");
}

/**
 * @brief Runs application based on parameters passed in. Those specify which user interface to use.
 * For all available interfaces, @see AbstractInterface::createInstance()
 * @param argc Number of arguments passed in.
 * @param argv Array of arguments passed in.
 * To specify which interface to use: --interface <INTERFACE_NAME>
 * If no interface is specified, console interface is used.
 * @return
 */
int main(int argc, char **argv)
{
  string interfaceName = "console";
  AbstractInterface *interface;
  try
  {
    interfaceName = getValue("--interface", argc, argv);
  }
  catch (const runtime_error &e)
  {
  }
  try
  {
    interface = AbstractInterface::createInstance(interfaceName);
  }
  catch (const runtime_error &e)
  {
    cout << e.what() << endl;
    return 1;
  }
  interface->run();
}
