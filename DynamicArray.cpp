#include "DynamicArray.h"

#include <cstdlib>
#include <utility>

template <typename T>
DynamicArray<T>::DynamicArray() : DynamicArray(1) {}

template <typename T>
DynamicArray<T>::DynamicArray(int capacity) {
  size_ = 0;
  capacity_ = capacity;
  data_ = (T *)std::malloc(capacity_ * sizeof(T));
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  data_ = (T *)std::malloc(capacity_ * sizeof(T));

  for (int i = 0; i < size_; i++) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  data_ = other.data_;

  other.data_ = nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  std::free(data_);
}

template <typename T>
T &DynamicArray<T>::operator=(DynamicArray<T> other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);

  return *this;
}

template <typename T>
int DynamicArray<T>::Insert(const T &value) {
  size_++;
  if (capacity_ <= size_) {
    capacity_ *= 2;
    T* new_arr = (T *)std::realloc(data_, capacity_ * sizeof(T));
    if (new_arr == nullptr) {
      return -1;
    }
    data_ = new_arr;
  }

  int index = size_ - 1;
  data_[index] = value;

  return index;
}

template <typename T>
int DynamicArray<T>::Insert(int index, const T &value) {
  // TODO: add move

  Insert(value);
  int new_index = index - 1;

  for (int i = size_ - 1; i > index; i--) {
    data_[i] = data_[i - 1];
  }

  data_[index] = value;

  return index;
}

template <typename T>
void DynamicArray<T>::Remove(int index) {
  for (int i = index; i < size_ - 1; i++) {
    data_[i] = data_[i + 1];
  }

  size_--;
}

template <typename T>
const T &DynamicArray<T>::operator[](int index) const {
  // TODO: вставьте здесь оператор return

  return data_[index];
}

template <typename T>
T &DynamicArray<T>::operator[](int index) {
  // TODO: вставьте здесь оператор return

  return data_[index];
}

template <typename T>
int DynamicArray<T>::Size() const {
  return this->size_;
}
