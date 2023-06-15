#include "./test.h"
#include "../user-interfaces/console/commands/console-command.h"
using namespace std;

/**
 * Run store to memory command. Returns true if command was successfully executed.
 * @param tokenizer
 * @param memory
 * @param command
 * @return
 */
bool runStoreToMemory(VariablesMemory &memory, const std::vector<Token> &command) {
  StoreExpressionToVariable storeCommand(memory);
  if (!storeCommand.matchesSyntactically(command)) {
    return false;
  }
  storeCommand.run(command);
  return true;
}
