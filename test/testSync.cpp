#define NUMBER_SIZE 10
#define SIGNATURE "_2"

LRUCache lruCache(NUMBER_SIZE);
static const string numbers[NUMBER_SIZE] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void putForward(){
  int i = 0;
  while(i<NUMBER_SIZE){
      lruCache.put(i, numbers[i]);
      i++;
  }
}

void putBackward(){
  int i = NUMBER_SIZE-1;
  while(i>-1){
      lruCache.put(i, numbers[i]+SIGNATURE);
      i--;
  }
}

/*thread 2 with signature + moving backward. Therefore, smaller numbers
shall be put by thread 2 and bigger numbers by thread 1*/
bool isSync(){
  int i = 0;
  bool isThread2 = true;
  while(i<NUMBER_SIZE){
      bool found = lruCache.get(i).find(SIGNATURE);
      if(isThread2 && !found)
        isThread2 = false;
      else if(!isThread2 && found)
        return false;
      i++;
  }
  return true;
}

/*one thread moving forward while the other moving backward,
they will have to meet, meaning accessing the same key-value*/
bool testSync(){
  thread thread1(putForward);
  thread thread2(putBackward);
  thread1.join();
  thread2.join();
  return isSync();
}
