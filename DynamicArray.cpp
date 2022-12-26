#include "DynamicArray.h"

#include <cassert>
#include <cstdlib>
#include <utility>

#ifdef _DEBUG
#include <iostream>
#endif

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
    new (data_ + i) T(other.data_[i]);
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
  for (int i = 0; i < size_; i++) {
    data_[i].~T();
  }
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
  if (size_ == capacity_) {
    capacity_ *= 2;
#ifdef TRY_USE_REALLOC
    T *new_arr = (T *)std::realloc((void *)data_, capacity_ * sizeof(T));
#else
    T *new_arr = (T *)std::malloc(capacity_ * sizeof(T));
#endif
    if (new_arr == nullptr) {
      return -1;
    }
    if (new_arr != data_) {
#ifdef _DEBUG
      std::cerr << "Reallocation happened at size = " << size_ << std::endl;
#endif
      for (int i = 0; i < size_; i++) {
        new (new_arr + i) T(std::move(data_[i]));
      }
      std::free(data_);
      data_ = new_arr;
    }
  }

  int index = size_ - 1;
  data_[index] = value;

  return index;
}

template <typename T>
int DynamicArray<T>::Insert(int index, const T &value) {
#ifdef _DEBUG
  assert(index >= 0 && index < size_ && "Out of bounds error");
#endif
  if (index == size_) {
    Insert(value);
    return index;
  }

  for (int i = size_ - 1; i > index; i--) {
    data_[i] = std::move(data_[i - 1]);
  }
  Insert(data_[size_ - 1]);

  T tmp = std::move(data_[size_ - 2]);
  for (int i = size_ - 2; i > index; i--) {
    new (data_ + i) T(std::move(data_[i - 1]));
  }
  new (data_ + index) T(value);

  return index;
}

template <typename T>
void DynamicArray<T>::Remove(int index) {
  data_[index].~T();
  for (int i = index; i < size_ - 1; i++) {
    new (data_ + i) T(std::move(data_[i + 1]));
  }
  size_--;
}

template <typename T>
const T &DynamicArray<T>::operator[](int index) const {
#ifdef _DEBUG
  assert(index >= 0 && index < size_ && "Out of bounds error");
#endif
  return data_[index];
}

template <typename T>
T &DynamicArray<T>::operator[](int index) {
#ifdef _DEBUG
  assert(index >= 0 && index < size_ && "Out of bounds error");
#endif
  return data_[index];
}

template <typename T>
int DynamicArray<T>::Size() const {
  return this->size_;
}