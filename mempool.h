#include <stdlib.h>
#include <string.h>
#include <vector>

#define DEFAULT_MEMPOOL_SIZE 16

template <class T> class MemPool {
private:
  unsigned size_;
  unsigned capacity_;

  // Contains large memory blocks
  // This is where the actual memory sits.
  std::vector<T *> markers_;

  // Contains the available memory addresses
  // When we need a new memory address, we will
  // select the address available at the top of this stack.
  T **memstack_;

public:
  MemPool(unsigned size = DEFAULT_MEMPOOL_SIZE)
      : size_(0), capacity_(std::max(size, (unsigned)DEFAULT_MEMPOOL_SIZE)) {

    T *new_block = (T *)calloc(capacity_, sizeof(T));
    markers_.push_back(new_block);

    memstack_ = (T **)calloc(capacity_, sizeof(T *));
    // Fill the stack with the available memory addresses.
    for (unsigned i = 0; i < capacity_; i++) {
      memstack_[i] = new_block + i;
    }
  }

  ~MemPool() {
    for (unsigned i = 0; i < markers_.size(); i++) {
      free(markers_[i]);
    }

    free(memstack_);
  }

  T *allocate() {
    if (size_ == capacity_) {
      // Free the old stack of addresses
      free(memstack_);

      // Allocated memory has filled, reallocate memory
      memstack_ = (T **)calloc(2 * capacity_, sizeof(T));

      T *new_block = (T *)calloc(capacity_, sizeof(T));

      // Keep track of the large memory blocks for destructor
      markers_.push_back(new_block);

      // Record the newly available addresses in the stack
      // Note that we don't care about the older addresses
      // since they are already allocated and given out.
      for (unsigned i = 0; i < capacity_; i++) {
        memstack_[capacity_ + i] = new_block + i;
      }

      capacity_ *= 2;
    }

    T *next = memstack_[size_++];
    bzero(next, sizeof(T));
    return next;
  }

  void deallocate(T *mem) {
    // mem location is now available
    // Add that at the top of the stack
    memstack_[size_--] = mem;
  }

  int size() { return size_; }
  int capacity() { return capacity_; }
};