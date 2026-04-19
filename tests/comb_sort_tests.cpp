// test_comb_sort.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "../myCombSort/myCombSort.h"

// ============================================
// Базовые тесты
// ============================================

TEST(CombSortTest, EmptyArray) {
  int* arr = nullptr;
  // Сортировка пустого массива не должна падать
  myCombSort(arr, 0);
  SUCCEED();
}

TEST(CombSortTest, SingleElement) {
  int arr[] = {42};
  myCombSort(arr, 1);
  EXPECT_EQ(arr[0], 42);
}

TEST(CombSortTest, TwoElementsSorted) {
  int arr[] = {1, 2};
  myCombSort(arr, 2);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
}

TEST(CombSortTest, TwoElementsUnsorted) {
  int arr[] = {2, 1};
  myCombSort(arr, 2);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
}

// ============================================
// Тесты на разных типах данных
// ============================================

TEST(CombSortTest, Integers) {
  int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
  int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  myCombSort(arr, 9);

  for (size_t i = 0; i < 9; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, Doubles) {
  double arr[] = {3.14, 1.41, 2.71, 0.58, 1.73};
  double expected[] = {0.58, 1.41, 1.73, 2.71, 3.14};

  myCombSort(arr, 5);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_DOUBLE_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, Strings) {
  std::string arr[] = {"banana", "apple", "cherry", "date"};
  std::string expected[] = {"apple", "banana", "cherry", "date"};

  myCombSort(arr, 4);

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, Chars) {
  char arr[] = {'d', 'a', 'c', 'b'};
  char expected[] = {'a', 'b', 'c', 'd'};

  myCombSort(arr, 4);

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================
// Тесты с разными компараторами
// ============================================

TEST(CombSortTest, DescendingOrder) {
  int arr[] = {1, 2, 3, 4, 5};
  int expected[] = {5, 4, 3, 2, 1};

  myCombSort(arr, 5, std::greater<int>());

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, CustomComparatorAbsolute) {
  // Сортировка по абсолютному значению
  int arr[] = {-5, 2, -1, 4, -3};
  int expected[] = {-1, 2, -3, 4, -5};  // |1|,|2|,|3|,|4|,|5|

  auto absCompare = [](int a, int b) { return std::abs(a) < std::abs(b); };

  myCombSort(arr, 5, absCompare);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================
// Краевые случаи
// ============================================

TEST(CombSortTest, AllElementsEqual) {
  int arr[] = {5, 5, 5, 5, 5};
  myCombSort(arr, 5);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 5);
  }
}

TEST(CombSortTest, AlreadySorted) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  myCombSort(arr, 10);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, ReverseSorted) {
  int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  myCombSort(arr, 10);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, NegativeNumbers) {
  int arr[] = {-3, -1, -7, -2, -5};
  int expected[] = {-7, -5, -3, -2, -1};

  myCombSort(arr, 5);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, MixedPositiveNegative) {
  int arr[] = {5, -2, 0, -8, 3, -1, 7};
  int expected[] = {-8, -2, -1, 0, 3, 5, 7};

  myCombSort(arr, 7);

  for (size_t i = 0; i < 7; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================
// Стресс-тесты
// ============================================

TEST(CombSortTest, LargeArray) {
  const size_t size = 10000;
  std::vector<int> arr(size);

  // Заполняем случайными числами
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10000);

  for (size_t i = 0; i < size; ++i) {
    arr[i] = dis(gen);
  }

  std::vector<int> expected = arr;
  std::sort(expected.begin(), expected.end());

  myCombSort(arr.data(), size);

  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(CombSortTest, LargeArrayWithDuplicates) {
  const size_t size = 5000;
  std::vector<int> arr(size);

  // Заполняем ограниченным набором значений
  for (size_t i = 0; i < size; ++i) {
    arr[i] = i % 100;
  }

  std::vector<int> expected = arr;
  std::sort(expected.begin(), expected.end());

  myCombSort(arr.data(), size);

  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================
// Тесты на устойчивость (для проверки)
// ============================================

struct Person {
  std::string name;
  int age;

  bool operator<(const Person& other) const { return age < other.age; }
};

TEST(CombSortTest, StructSorting) {
  Person arr[] = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}, {"David", 20}};

  Person expected[] = {
      {"David", 20}, {"Bob", 25}, {"Alice", 30}, {"Charlie", 35}};

  myCombSort(arr, 4);

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i].name, expected[i].name);
    EXPECT_EQ(arr[i].age, expected[i].age);
  }
}

// ============================================
// Тесты производительности (ручная проверка)
// ============================================

TEST(CombSortTest, PerformanceCheck) {
  const size_t size = 100000;
  std::vector<int> arr(size);

  for (size_t i = 0; i < size; ++i) {
    arr[i] = size - i;  // обратный порядок
  }

  auto start = std::chrono::high_resolution_clock::now();
  myCombSort(arr.data(), size);
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  // Проверяем, что отсортировано
  for (size_t i = 1; i < size; ++i) {
    EXPECT_LE(arr[i - 1], arr[i]);
  }

  std::cout << "Sorting " << size << " elements took " << duration.count()
            << " ms\n";
}

// ============================================
// Основная функция
// ============================================

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}