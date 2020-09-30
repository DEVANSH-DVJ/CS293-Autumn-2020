#include <iostream>

bool is_already_distributed(int a[], int k, int n) {
  int q = n / k;
  for (int i = 0; (i < k); i++)
    if ((a[i] < q) || (a[i] > q + 1))
      return false;
  return true;
}

void distribute(int a[], int k, int i) {
  if (i >= k)
    return;

  int n_i = a[i];
  int loops = a[i] / k;
  int extra = a[i] % k;

  if (loops)
    for (int j = 0; j < k; j++)
      a[j] += loops;

  for (int j = 0; j < extra; j++)
    a[(i + j + 1) % k]++;

  a[i] -= n_i;

  // for (int i = 0; i < k; i++)
  //   std::cout << a[i] << " ";

  // std::cout << std::endl;

  return;
}

void redistribute(int a[], int k, int n) {
  if (a[0] == n)
    return;

  int i = 1;
  for (; i < k; i++) {
    if (a[i] != 0)
      break;
  }
  // std::cout << i << ";;;\n";

  for (; i < k; i++) {
    distribute(a, k, i);
    std::cout << i << " ";
  }

  return redistribute(a, k, n);
}

int main() {
  int n, k;
  std::cin >> n >> k;
  int a[k];

  for (int i = 0; i < k; i++)
    std::cin >> a[i];

  if (is_already_distributed(a, k, n))
    return 0;

  // distribute(a, k, 2);
  // distribute(a, k, 1);
  // distribute(a, k, 1);
  // distribute(a, k, 2);
  // distribute(a, k, 2);
  // distribute(a, k, 1);
  // distribute(a, k, 2);

  redistribute(a, k, n);
  distribute(a, k, 0);
  std::cout << 0 << "\n";

  // for (int i = 0; i < k; i++)
  //   std::cout << a[i] << " ";
  // std::cout << std::endl;

  return 0;
}

// For n <= 100000 and k <= 100, time taken is less than 0.008 seconds.

// (Stress check)
// For n <= 1000000 and k <= 1000, time taken is less than 0.300 seconds.
