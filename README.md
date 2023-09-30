# bounded_queue

Bounded queue contains two implementations of bounded concurrent queues: multithreaded lock-based queue and single-producer single-consumer lock-free and wait-free queue written in C++17.

## Example
```cpp
#include "bounded_queue_mt.hpp"

bounded_queue_mt<int> q;
std::vector<int> vec;
std::thread t1([&] { q.push(1); });
std::thread t2([&] { q.push(2); });
std::thread t3([&] { vec.push_back(q.pop()); });
std::thread t4([&] { vec.push_back(q.pop()); });
t1.join();
t2.join();
t3.join();
t4.join();
```
