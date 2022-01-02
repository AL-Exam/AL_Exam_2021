#ifndef LOCK_GUARD_H_
#define LOCK_GUARD_H_
#include <mutex>

// Аккуратно, очень сложное задание)))
template <class Mutex>
class LockGuard {
 public:
  explicit LockGuard(Mutex& m) : mutex_(m) { mutex_.lock(); }
  LockGuard(Mutex& m, std::adopt_lock_t t) : mutex_(m) {}
  ~LockGuard() { mutex_.unlock(); }

  LockGuard(const LockGuard&) = delete;
  LockGuard& operator=(const LockGuard&) = delete;

 private:
  Mutex& mutex_;
};

#endif  // LOCK_GUARD_H_
