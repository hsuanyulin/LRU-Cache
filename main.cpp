#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <thread>
#include <string>
#include "LRUCache/LRUCache.h"
#include "test/testLRU.h"
#include "test/testSync.cpp"
using namespace std;

int main() {
  testSync();

  cout << "Testing cache functions.";
  CPPUNIT_NS::TestResult testResult;
  CPPUNIT_NS::TestResultCollector collectedResults;
  CPPUNIT_NS::BriefTestProgressListener progress;
  testResult.addListener (&collectedResults);
  testResult.addListener (&progress);
  CPPUNIT_NS::TextUi::TestRunner runner;
  runner.addTest(LRUTestCase::suite());

  bool isSuccessed = runner.run();

  CPPUNIT_NS::CompilerOutputter output(&collectedResults, cerr);
  output.write ();

  return isSuccessed?0:1;
}
