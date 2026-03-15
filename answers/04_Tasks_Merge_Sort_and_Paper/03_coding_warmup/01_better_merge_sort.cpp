#include <algorithm>
#include <cstring>
#include <iostream>
#include <omp.h>
#include <random>
using namespace std;

vector<int> get_random_int_vector(int n) {
  default_random_engine re{random_device{}()};
  uniform_int_distribution<int> next_rand{INT32_MIN, INT32_MAX};
  vector<int> v(n);
  for (auto &num : v) {
    num = next_rand(re);
  }
  return v;
}

inline void merge(const int *__restrict__ a, const int *__restrict__ b,
                  int *__restrict__ c, const int a_size, const int b_size,
                  const int c_size) {
  int idx_a = 0;
  int idx_b = 0;
  for (int i = 0; i < c_size; ++i) {
    if (idx_a == a_size) {
      c[i] = b[idx_b++];
    } else if (idx_b == b_size) {
      c[i] = a[idx_a++];
    } else {
      c[i] = (a[idx_a] < b[idx_b]) ? a[idx_a++] : b[idx_b++];
    }
  }
}

void insertion_sort(int *arr, int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

void merge_sort_better(int *arr, int n) {
  if (n > 1) {
    if (n < 50){
      insertion_sort(arr, n);
      return;
    }
    const int size_a = n / 2;
    const int size_b = n - size_a;
    #pragma omp task if (size_a > 10000)
    {
      merge_sort_better(arr, size_a);
    }
    merge_sort_better(arr + size_a, size_b);
    #pragma omp taskwait
    if (n < 10000) {
      int* c = (int*) alloca(n * sizeof(int));
      merge(arr, arr + size_a, c, size_a, size_b, n);
      memcpy(arr, c, sizeof(int) * n);
      return;
    }
    int *c = new int[n];
    merge(arr, arr + size_a, c, size_a, size_b, n);
    memcpy(arr, c, sizeof(int) * n);
    delete[](c);
  }
}

int main(int argc, char *argv[]) {
  const int n = 100000000;
  vector<int> v = get_random_int_vector(n);
  vector<int> v_copy = v;

  double start = omp_get_wtime();
  #pragma omp parallel
    #pragma omp single nowait
    {
      merge_sort_better(v.data(), n);
    }
  cout << "naive: " << omp_get_wtime() - start << " seconds" << endl;

  start = omp_get_wtime();
  sort(begin(v_copy), end(v_copy));
  cout << "std::sort: " << omp_get_wtime() - start << " seconds" << endl;

  if (v != v_copy) {
    cout << "sort implementation is buggy\n";
  }
}
