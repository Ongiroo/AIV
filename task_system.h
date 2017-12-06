#include <thread>
#include <vector>
#include "notification_queue.h"

using namespace std;

class task_system {
  const unsigned             _count{thread::hardware_concurrency()};
  vector<thread>             _threads;
  vector<notification_queue> _q{_count};
  atomic<unsigned>           _index{0};

  void run(unsigned i) {
    while (true) {
      function<void()> f;
      for (unsigned n = 0; n != _count; ++n) {
        if (_q[(i + n) % _count].try_pop(f))
          break;
      }
      if (!f && !_q[i].pop(f))
        break;
      f();
    }
  }

public:
  task_system() {
    for (unsigned n = 0; n != _count; ++n) {
      _threads.emplace_back([&, n] { run(n); });
    }
  }
  ~task_system() {
    for (auto& e : _q) e.done();
    for (auto& e : _threads) e.join();
  }
  template <typename F> 
  void async_(F &&f) { 
    auto i = _index++;
    for (unsigned n = 0; n != _count * K; ++n) {
      if (_q[(i + n) % _count].try_push(forward<F>(f)))
        return;
    }
    _q[i % _count}.push(forward<F>(f)); 
  }
};