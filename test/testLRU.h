#ifndef LRU_TEST_H
#define LRU_TEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "../LRUCache/LRUCache.h"
#define NUMBER_SIZE 10
#define MEMORY_MAX 2
using namespace std;

class LRUTestCase :  public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(LRUTestCase);
      CPPUNIT_TEST(testPolicy);
      CPPUNIT_TEST(testErase);
  CPPUNIT_TEST_SUITE_END();

protected:
    void testPolicy(){
        LRUCache lruCache(MEMORY_MAX);
        lruCache.put(2, numbers[2]);
        CPPUNIT_ASSERT_EQUAL(numbers[2], lruCache.get(2));
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(1));
        lruCache.put(1, numbers[1]);
        CPPUNIT_ASSERT_EQUAL(numbers[1], lruCache.get(1));
        CPPUNIT_ASSERT_EQUAL(numbers[2], lruCache.get(2));
        /* 1 is the last recent used one: 1 is evicted */
        lruCache.put(8, numbers[8]);
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(1));
        CPPUNIT_ASSERT_EQUAL(numbers[8], lruCache.get(8));
    }
    void testErase(){
        LRUCache lruCache(MEMORY_MAX);
        lruCache.put(2, numbers[2]);
        CPPUNIT_ASSERT_EQUAL(numbers[2], lruCache.get(2));
        //delete the only element in the queue
        lruCache.erase(2);
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(2));
        lruCache.put(1, numbers[1]);
        CPPUNIT_ASSERT_EQUAL(numbers[1], lruCache.get(1));
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(2));
        lruCache.put(8, numbers[8]);
        CPPUNIT_ASSERT_EQUAL(numbers[1], lruCache.get(1));
        CPPUNIT_ASSERT_EQUAL(numbers[8], lruCache.get(8));
        lruCache.put(2, numbers[2]);
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(1));
        CPPUNIT_ASSERT_EQUAL(numbers[2], lruCache.get(2));
        lruCache.put(7, numbers[7]);
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(8));
        CPPUNIT_ASSERT_EQUAL(numbers[2], lruCache.get(2));
        //delete the front of the queue
        lruCache.erase(2);
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(2));
        lruCache.put(6, numbers[6]);
        //delete the end of the queue
        lruCache.erase(7);
        CPPUNIT_ASSERT_EQUAL(numbers[6], lruCache.get(6));
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(2));
        CPPUNIT_ASSERT_EQUAL(ERROR_NO_KEY, lruCache.get(7));
    }
private:
  const string numbers[NUMBER_SIZE] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const string ERROR_NO_KEY = "Key does not exist";
};

#endif
