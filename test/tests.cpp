#include <mempool.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("test_my_header") {
  unsigned capacity = 1024;
  MemPool<int> pool(capacity);
  std::vector<int *> locations;

  for (auto i = 0u; i < capacity * 2; i++) {
    int *location = pool.allocate();
    locations.push_back(location);
  }

  for (auto i = 0u; i < capacity * 2; i++) {
    pool.deallocate(locations[i]);
  }
}