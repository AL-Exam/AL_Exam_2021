//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_SAFE_QUEUE_H
#define EXAM_SAFE_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class SafeQueue {
  std::queue<T> _data;
  std::mutex mutex;
 public:
  T Pop(){
    T temp = _data.front();
    mutex.lock();
    _data.pop();
    mutex.unlock();
  }
  void Push(const T& value){
    mutex.lock();
    _data.push(value);
    mutex.unlock();
  }
  bool TryPop(T& value){
    return mutex.try_lock();
  }
};

#endif  // EXAM_SAFE_QUEUE_H
