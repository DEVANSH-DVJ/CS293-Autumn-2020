#include <iostream>

class Algo {
private:
  void fill_arr() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        arr[i][j] = 0;
    }
    for (int i = 0; i < n; i++) {
      arr[0][i] = 1;
    }

    for (int i = 1; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (j < n - i)
          arr[i][j] = arr[i - 1][j] * (j + 1) + arr[i - 1][j + 1];
      }
    }
  }

  void cummulate() {
    long long int row_sum, temp;
    for (int i = 0; i < n; i++) {
      row_sum = 0;
      for (int j = 0; j < n; j++) {
        row_sum += arr[i][j];
        arr[i][j] = row_sum;
        // temp = arr[i][j];
        // arr[i][j] = row_sum;
        // row_sum += temp;
      }
    }
  }

public:
  long long int **arr;
  int n;

  Algo(int const size) {
    n = size;
    arr = (long long int **)malloc(n * sizeof(long long int *));
    for (int i = 0; i < n; i++)
      arr[i] = (long long int *)malloc(n * sizeof(long long int));
    // arr = new (*int)[n];
    // for (int i = 0; i < n; i++) {
    //   arr[i] = new int[n];
    // }
    fill_arr();
    cummulate();
  }

  ~Algo() { delete arr; }
};

long long int get_sub(int n, int arr[], int k) {
  if (n == k)
    return 1;

  int max = 0;
  for (int i = 0; i < k; i++) {
    if (arr[i] > max)
      max = arr[i];
  }

  int sub = 0;
  for (int i = 0; i <= max + 1; i++) {
    arr[k] = i;
    sub += get_sub(n, arr, k + 1);
  }

  return sub;
}

long long int get_rank(int arr[], int n, long long int **given) {
  long long int count = 0;

  int max = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] == 0)
      continue;
    count += given[n-1-i][arr];
    // if (max < arr[i]-1)
    //   max = arr[i]-1;
  }


  // int max = 0;
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < arr[i]; j++) {
  //     // if (max < j)
  //     //   max = j;
  //     count += given[n - 1 - i][max];
  //     // std::cout << given[n-1-i][max] << "//";
  //   }
  //   if (max < arr[i])
  //     max = arr[i];
  // }

  // int k = n;
  // while (k > 0) {
  //   // std::cout << k << "\n";
  //   if (arr[k - 1] == 0) {
  //     k--;
  //     continue;
  //   }
  //   arr[k - 1]--;
  //   count += get_sub(n, arr, k, given);
  // }

  return count;
}

int *get_array(int r, int n, long long int **given) {}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, t;
  std::cin >> n >> t;
  int a[n]; // Input Array

  Algo given(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << given.arr[i][j] << " ";
    }
    std::cout << std::endl;
  }

  char ch;         // Initial character
  long long int r; // Input Rank
  for (int j = 0; j < t; j++) {
    std::cin >> ch;
    if (ch == 'R') {
      for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        // std::cout << "//\n";
      }
      std::cout << get_rank(a, n, given.arr) << std::endl;
    } else if (ch == 'U') {
      std::cin >> r;
      // a = get_array(r, n);
      // for (int i = 0; i < n; i++) {
      //   std::cout << a[i] << " ";
      // }
      std::cout << std::endl;
    }
  }
  // int n2 = 4;
  // int a[4] = {0, 1, 2, 2};

  // std::cout << get_sub(n2, a, n2-2) << std::endl;
}
