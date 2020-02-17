#include "../search/mutexpool.h"

using namespace std;

Mutex::Mutex() {
  lock = false;
}

void Lock::lock() {
  while(mutex->lock.exchange(true, memory_order_acquire)) {
    while (mutex->lock.load(memory_order_relaxed));
  }
  ownsLock = true;
}

void Lock::unlock() {
  mutex->lock.store(false, memory_order_release);
  ownsLock = false;
}

Lock::Lock(Mutex &m) {
  mutex = &m;
  lock();
}

Lock::~Lock() {
  if (ownsLock) {
    unlock();
  }
}

MutexPoolSpinlock::MutexPoolSpinlock(uint32_t n) {
  numMutexes = n;
  mutexes = new Mutex[n];
}

MutexPoolSpinlock::~MutexPoolSpinlock() {
  delete[] mutexes;
}

uint32_t MutexPoolSpinlock::getNumMutexes() const {
  return numMutexes;
}

Mutex& MutexPoolSpinlock::getMutex(uint32_t idx) {
  return mutexes[idx];
}

MutexPool::MutexPool(uint32_t n) {
  numMutexes = n;
  mutexes = new mutex[n];
}

MutexPool::~MutexPool() {
  delete[] mutexes;
}

uint32_t MutexPool::getNumMutexes() const {
  return numMutexes;
}

mutex& MutexPool::getMutex(uint32_t idx) {
  return mutexes[idx];
}
