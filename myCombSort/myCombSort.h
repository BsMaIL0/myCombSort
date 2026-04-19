#ifndef MY_COMB_SORT_H
#define MY_COMB_SORT_H

#include <cmath>
#include <utility>

template <typename T, typename Compare = std::less<T>>
void myCombSort(T* array, size_t size, Compare comp = Compare()) {
  const double factor = 1.247;
  double gapFactor = static_cast<double>(size) / factor;
  bool swapped = true;

  while (gapFactor > 1 || swapped) {
    size_t gap = static_cast<size_t>(std::floor(gapFactor));
    if (gap < 1) {
      gap = 1;
    }

    swapped = false;

    for (size_t i = 0, j = gap; j < size; ++i, ++j) {
      if (comp(array[j], array[i])) {
        std::swap(array[i], array[j]);
        swapped = true;
      }
    }
    gapFactor = gapFactor / factor;
  }
}

#endif  // MY_COMB_SORT_H