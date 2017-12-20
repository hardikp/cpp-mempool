[![Build Status](https://travis-ci.org/hardikp/cpp-mempool.svg?branch=master)](https://travis-ci.org/hardikp/cpp-mempool)

# cpp-mempool
C++ header-only mempool library

## Examples
```C++
#include <mempool.h>

int main(int argc, char** argv) {
  unsigned capacity = 1024;
  MemPool<int> pool(capacity);

  for (auto i = 0u; i < capacity * 2; i++) {
    int *location = pool.allocate();
  }
}
```

## Notes
* `MemPool` is not thread-safe. If you're trying to use a single memory pool from multiple threads, it can create race conditions.
