#ifndef SEMESTRAL_TEST_LIST_H
#define SEMESTRAL_TEST_LIST_H

// this is relative to makefile location
#define TEST_ASSETS_DIR "./src/test/assets/"
#define TEST_CSV_1 TEST_ASSETS_DIR "test.csv"
#define TEST_CSV_SET_1 TEST_ASSETS_DIR "test-set1.csv"
#define TEST_CSV_SET_2 TEST_ASSETS_DIR "test-set2.csv"
#define TEST_CSV_4 TEST_ASSETS_DIR "test10.csv"
#define TEST_JSON_FILE TEST_ASSETS_DIR "test.json"
#define TEST_JSON_ERROR_1 TEST_ASSETS_DIR "test-error1.json"
#define TEST_JSON_ERROR_2 TEST_ASSETS_DIR "test-error2.json"
#include <cassert>
#include "../user-interfaces/abstract/variables-memory.h"
#include "../user-interfaces/string-parsing/tokenizer/token.h"
#include "../user-interfaces/string-parsing/tokenizer/tokenizer.h"

bool runStoreToMemory(VariablesMemory &memory, const std::vector<Token> &command);

void testCsvDataSource();
void testJSONDataSource();
void testTokenizeMethod();
void testConsoleCommands();
void testExpression();
void testUtils();

#endif //SEMESTRAL_TEST_LIST_H
