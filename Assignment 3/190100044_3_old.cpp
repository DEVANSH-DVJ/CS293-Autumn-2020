#include <iostream>

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

long long int get_rank(int arr[], int n) {
  long long int count = 0;

  int k = n;
  while (k > 0) {
    // std::cout << k << "\n";
    if (arr[k - 1] == 0) {
      k--;
      continue;
    }
    arr[k - 1]--;
    count += get_sub(n, arr, k);
  }

  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, t;
  std::cin >> n >> t;
  int a[n]; // Input Array

  char ch; // Initial character
  long long int r; // Input Rank
  for (int j = 0; j < t; j++) {
    std::cin >> ch;
    if (ch=='R') {
      for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        // std::cout << "//\n";
      }
      std::cout << get_rank(a, n) << std::endl;
    }
    else if (ch == 'U') {
      std::cin >> r;
      // a = get_array(r, n);
      // for (int i = 0; i < n; i++) {
      //   std::cout << a[i] << " ";
      // }
      std::cout << std::endl;
    }
  }
  // int n = 4;
  // int a[4] = {0, 1, 2, 2};

  // std::cout << get_rank(a, n) << std::endl;
}
