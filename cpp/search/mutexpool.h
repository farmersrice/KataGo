#ifndef SEARCH_MUTEXPOOL_H_
#define SEARCH_MUTEXPOOL_H_

#include "../core/global.h"
#include "../core/multithread.h"

#include <atomic>

struct Mutex {
  std::atomic<bool> lock;
  Mutex();
};

struct Lock {
  void lock();
  void unlock();

  Lock(Mutex &m);
  ~Lock();

  Mutex* mutex;
  bool ownsLock;
};

class MutexPoolSpinlock {
  Mutex* mutexes;
  uint32_t numMutexes;

 public:
  MutexPoolSpinlock(uint32_t n);
  ~MutexPoolSpinlock();

  uint32_t getNumMutexes() const;
  Mutex& getMutex(uint32_t idx);
};

class MutexPool {
  std::mutex* mutexes;
  uint32_t numMutexes;

 public:
  MutexPool(uint32_t n);
  ~MutexPool();

  uint32_t getNumMutexes() const;
  std::mutex& getMutex(uint32_t idx);
};


#endif  // SEARCH_MUTEXPOOL_H_
