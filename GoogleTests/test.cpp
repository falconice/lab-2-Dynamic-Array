#include <algorithm>
#include <vector>
#include "pch.h"
#include "../DynamicArray.cpp"


TEST(BasicArrayFunctions, Insert) {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i + 1);
  for (int i = 0; i < 10; ++i) ASSERT_EQ(dynamic_array[i], i + 1);
}

TEST(BasicArrayFunctions, Remove) {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i + 1);
  for (int i = 0; i < 3; ++i) dynamic_array.Remove(0);
  for (int i = 0; i < 7; ++i) ASSERT_EQ(dynamic_array[i], i + 1 + 3);
}

TEST(BasicArrayFunctions, Multiplication) {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i);
  for (int i = 0; i < 10; ++i) dynamic_array[i] *= 3;
  for (int i = 0; i < 10; ++i) ASSERT_EQ(dynamic_array[i], i * 3);
}

TEST(IteratorFunctions, Get) {
  DynamicArray<int> dynamic_array;

  dynamic_array.Insert(2);
  dynamic_array.Insert(4);
  dynamic_array.Insert(5);
  dynamic_array.Insert(1);
  dynamic_array.Insert(6);
  dynamic_array.Insert(3);

  std::vector<int> v{2, 4, 5, 1, 6, 3};

  auto it2 = v.begin();
  for (auto it = dynamic_array.begin(); it.HasNext() && it2 != v.end();
       it.Next(), it2++)
    ASSERT_EQ(it.Get(), *it2);
}
