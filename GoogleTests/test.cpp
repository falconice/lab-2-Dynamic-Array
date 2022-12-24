#include "pch.h"
#include "../DynamicArray.cpp"

TEST(TestCaseName, TestName) {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i + 1);
  for (int i = 0; i < 10; ++i) ASSERT_EQ(dynamic_array[i], i + 1);
}

TEST(TestCaseName, TestName2) {
  DynamicArray<int> dynamic_array;
  for (int i = 0; i < 10; ++i) dynamic_array.Insert(i);
  for (int i = 0; i < 10; ++i) dynamic_array[i] *= 3;
  for (int i = 0; i < 10; ++i) ASSERT_EQ(dynamic_array[i], i * 3);
}
