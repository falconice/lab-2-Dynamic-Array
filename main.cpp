// lab-2-DynamicArray.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//

#include <iostream>

#include "DynamicArray.cpp"
#include "DynamicArray.h"

int main() {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i + 1);

  for (int i = 0; i < dynamic_array.Size(); ++i) dynamic_array[i] *= 2;
  for (auto it = dynamic_array.begin(); it.HasNext(); it.Next())
    std::cout << it.Get() << std::endl;

  for (auto it = dynamic_array.crbegin(); it.HasNext(); it.Next())
    std::cout << it.Get() << std::endl;


  std::cout << "Hello World!\n";
}
