#pragma once

#include <iterator>
#include <utility>

template <typename T>

class DynamicArray final {
 private:
  template <typename DynamicArrayType, typename G, bool isReversed>
  class ArrayIterator_t;

 public:
  DynamicArray();
  DynamicArray(int capacity);
  DynamicArray(const DynamicArray<T>& other);
  DynamicArray(DynamicArray<T>&& other);
  ~DynamicArray();

  T& operator=(DynamicArray<T> other);

  int Insert(const T& value);
  int Insert(int index, const T& value);

  void Remove(int index);

  const T& operator[](int index) const;
  T& operator[](int index);

  int Size() const;

  using Iterator = ArrayIterator_t<DynamicArray<T>, T, false>;
  Iterator begin() {
    return Iterator(this);
  }
  Iterator end() {
    return Iterator(this, size_);
  }

  using ConstIterator = ArrayIterator_t<const DynamicArray<T>, const T, false>;
  ConstIterator cbegin() const {
    return ConstIterator(this);
  }
  ConstIterator cend() const {
    return DynamicArray<T>::ConstIterator(this, size_);
  }

  using ReversedIterator = ArrayIterator_t<DynamicArray<T>, T, true>;
  ReversedIterator rbegin() {
    return ReversedIterator(this, size_ - 1);
  }
  ReversedIterator rend() {
    return ReversedIterator(this, -1);
  }

  using ConstReversedIterator =
      ArrayIterator_t<const DynamicArray<T>, const T, true>;

  ConstReversedIterator crbegin() const {
    return ConstReversedIterator(this, size_ - 1);
  }

  ConstReversedIterator crend() const {
    return DynamicArray<T>::ConstReversedIterator(this, -1);
  }

 private:
  T* data_;
  int capacity_;
  int size_;

  // Iterator
  template <typename DynamicArrayType, typename G, bool isReversed>
  class ArrayIterator_t
      : public std::iterator<std::bidirectional_iterator_tag, G> {
   public:
    friend DynamicArrayType;

    // copy
    ArrayIterator_t(
        const ArrayIterator_t<DynamicArrayType, G, isReversed>& other)
        : dynamic_array_(other.dynamic_array_), position_(other.position_) {}

    // move
    ArrayIterator_t(
        const ArrayIterator_t<DynamicArrayType, G, isReversed>&& other)
        : dynamic_array_(other.dynamic_array_), position_(other.position_) {
      other.dynamic_array_ = nullptr;
    }

    ArrayIterator_t& operator=(
        ArrayIterator_t<DynamicArrayType, G, isReversed> other) {
      std::swap(dynamic_array_, other.dynamic_array_);
      std::swap(position_, other.position_);
      return *this;
    };

    // pref increment ++i
    ArrayIterator_t& operator++() {
      if (isReversed) {
        position_--;
        if (position_ < -1) {
          position_ = -1;
        }
      } else {
        position_++;

        // boundaries check
        if (position_ > dynamic_array_->Size()) {
          position_ = dynamic_array_->Size();
        }
      }
      return *this;
    }

    // post increment i++
    ArrayIterator_t operator++(int) {
      ArrayIterator_t<DynamicArrayType, G, isReversed> result(*this);
      operator++();
      return result;
    }

    // pref deccrement --i
    ArrayIterator_t& operator--() {
      if (isReversed) {
        position_++;
        // boundaries check
        if (position_ > dynamic_array_->Size()) {
          position_ = dynamic_array_->Size();
        }
      } else {
        position_--;
        if (position_ < -1) {
          position_ = -1;
        }
      }
      return *this;
    }

    // post deccrement i--
    ArrayIterator_t operator--(int) {
      // current position for result
      ArrayIterator_t<DynamicArrayType, G, isReversed> result(*this);
      operator--();
      return result;
    }

    bool operator==(
        const ArrayIterator_t<DynamicArrayType, G, isReversed>& other) const {
      return dynamic_array_ == other.dynamic_array_ &&
             position_ == other.position_;
    }

    bool operator!=(
        const ArrayIterator_t<DynamicArrayType, G, isReversed>& other) const {
      return !operator==(other);
    }
    bool operator<(
        const ArrayIterator_t<DynamicArrayType, G, isReversed>& other) const {
      if (isReversed) {
        return dynamic_array_ == other.dynamic_array_ &&
               position_ > other.position_;
      } else {
        return dynamic_array_ == other.dynamic_array_ &&
               position_ < other.position_;
      }
    }

    G& operator*() const {
      return (*dynamic_array_)[position_];
    }

    bool HasNext() const {
      if (isReversed) {
        return position_ > -1;
      } else {
        return position_ < dynamic_array_->Size();
      }
    }
    void Next() {
      operator++();
    }
    G& Get() const {
      return operator*();
    };
    void Set(const T& value) {
      operator*() = value;
    };

   private:
    DynamicArrayType* dynamic_array_;
    int position_;

    ArrayIterator_t(DynamicArrayType* dynamic_array_)
        : dynamic_array_(dynamic_array_), position_(0) {}

    ArrayIterator_t(DynamicArrayType* dynamic_array_, int position_)
        : dynamic_array_(dynamic_array_), position_(position_) {}
  };
};