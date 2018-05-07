#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <thread>
#include <string>
#include "LRUCache/LRUCache.h"
#include "test/testLRU.h"
#include "test/testSync.cpp"
using namespace std;

int main() {
  cout << "Testing cache functions.";
  CPPUNIT_NS::TextUi::TestRunner runner;
  runner.addTest(LRUTestCase::suite());

  return runner.run() & testSync();
}
