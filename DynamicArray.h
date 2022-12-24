#pragma once
template <typename T>

class DynamicArray final {
 public:
  DynamicArray();                              //+
  DynamicArray(int capacity);                  //+
  DynamicArray(const DynamicArray<T> &other);  //+ copy 
  DynamicArray(DynamicArray<T> &&other);       //+ move
  ~DynamicArray();                             //+

  T &operator=(DynamicArray<T> other);  //+оператор = присваивания

  int Insert(const T &value);             //+ return index &increase
  int Insert(int index, const T &value);  //+ return index

  void Remove(int index); //+

  const T &operator[](int index) const;//+
  T &operator[](int index); //+

  int Size() const; //+

  // friend
  /* Iterator iterator();
   ConstIterator iterator() const;

   Iterator reverseIterator();
   ConstIterator reverseIterator() const;*/

 private:
  T *data_;
  int capacity_;
  int size_;
};
