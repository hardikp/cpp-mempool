#include <vector>

#define DEFAULT_MEMPOOL_SIZE 16

template <class T> class MemPool {
private:
  unsigned size_;
  unsigned capacity_;

  std::vector<T *> markers_;
  T **memstack_;

public:
  MemPool(unsigned size = DEFAULT_MEMPOOL_SIZE)
      : size_(size), capacity_(std::max(size, (unsigned)DEFAULT_MEMPOOL_SIZE)) {

    T *new_block = (T *)calloc(capacity_, sizeof(T));
    markers_.push_back(new_block);
    memstack_ = (T **)calloc(capacity_, sizeof(T *));
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

  T *Allocate() {
    if (size_ == markers_) {
      // Allocated memory has filled, reallocate memory
      free(memstack_);
      T *new_block = (T *)calloc(capacity_, sizeof(T));
      markers_.push_back(new_block);
      memstack_ = (T **)calloc(2 * capacity_, sizeof(T));
      for (unsigned i = 0; i < capacity_; i++) {
        memstack_[capacity_ + i] = new_block[i];
      }
      capacity_ *= 2;
    }
    T *next = memstack_[size_++];
    bzero(next, sizeof(T));
    return next;
  }

  void DeAllocate(T *mem) {
    // Decrease the pointer
    memstack_[size_--] = mem;
  }
};