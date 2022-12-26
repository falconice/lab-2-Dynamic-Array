// lab-2-DynamicArray.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>

#include "DynamicArray.cpp"
#include "DynamicArray.h"

int main() {
  using CurType = std::string;
  DynamicArray<CurType> dynamic_array;
  // std::vector<CurType> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<CurType> v{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};

  for (auto el : v) {
    dynamic_array.Insert(el);
  }
  for (int i = 0; i < 2; ++i) {
    dynamic_array.Remove(i);
  }

  for (int i = 0; i < dynamic_array.Size(); ++i) {
    dynamic_array[i] += dynamic_array[i];
  }
  for (auto el : dynamic_array) {
    std::cout << el << std::endl;
  }

  for (auto it = dynamic_array.crbegin(); it.HasNext(); it.Next()) {
    std::cout << it.Get() << std::endl;
  }

#ifdef ASSERT_CHECK
  std::cout "dynamic_array[-1] = " << dynamic_array[-1] << std::endl;
#endif
}