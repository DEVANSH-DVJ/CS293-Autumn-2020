#include <iostream>
using namespace std;

void small_to_big(long long int *small_f, long long int *big_f, unsigned int n,
                  unsigned int start) {
  if (n == 0) {
    big_f[start] = small_f[start];
    return;
  }

  small_to_big(small_f, big_f, n - 1, start);
  small_to_big(small_f, big_f, n - 1, start + (1 << (n - 1)));

  for (unsigned int i = start + (1 << (n - 1)), j = i - (1 << (n - 1));
       i < start + (1 << n); i++, j++) {
    big_f[i] += big_f[j];
  }

  return;
}

void big_to_small(long long int *small_f, long long int *big_f, unsigned int n,
                  unsigned int start) {
  if (n == 0) {
    small_f[start] = big_f[start];
    return;
  }

  big_to_small(small_f, big_f, n - 1, start);
  big_to_small(small_f, big_f, n - 1, start + (1 << (n - 1)));

  for (unsigned int i = start + (1 << (n - 1)), j = i - (1 << (n - 1));
       i < start + (1 << n); i++, j++) {
    small_f[i] -= small_f[j];
  }

  return;
}

void final(long long int *small_f, long long int *big_f, unsigned int n,
           bool *is_big, unsigned int start) {
  if (n == 0) {
    if (is_big[start]) {
      small_f[start] = big_f[start];
    } else {
      big_f[start] = small_f[start];
    }

    return;
  }

  final(small_f, big_f, n - 1, is_big, start);
  final(small_f, big_f, n - 1, is_big, start + (1 << (n - 1)));

  for (unsigned int i = start + (1 << (n - 1)), j = i - (1 << (n - 1));
       i < start + (1 << n); i++, j++) {
    if (is_big[i]) {
      small_f[i] -= small_f[j];
    } else {
      big_f[i] += big_f[j];
      for (unsigned int k = i + 1; k < start + (1 << n); k++) {
          cout << i << "//" << k << "//\n";
        if (i & ~k == 0) {
          cout << i << "//" << k << "//\n";
          if (is_big[k]) {
            small_f[k] -= big_f[j];
          }
        }
      }
    }
  }

  return;
}

int main() {
  unsigned int n;
  long long int *small_f, *big_f;
  bool *is_big;

  cin >> n;
  small_f = new long long int[(1 << n)];
  big_f = new long long int[(1 << n)];
  for (unsigned int i = 0; i < (1 << n); i++) {
    cin >> small_f[i];
  }

  small_to_big(small_f, big_f, n, 0);
  big_to_small(small_f, big_f, n, 0);

  for (unsigned int i = 0; i < (1 << n); i++) {
    cout << big_f[i] << " ";
  }
  cout << endl;

  // for (unsigned int i = 0; i < (1 << n); i++) {
  //   cout << small_f[i] << " ";
  // }
  // cout << endl;

  is_big = new bool[(1 << n)];
  for (unsigned int i = 0; i < (1 << n); i++) {
    cin >> is_big[i];
    if (is_big[i]) {
      big_f[i] = small_f[i];
      small_f[i] = 0;
    } else {
      big_f[i] = 0;
    }
  }

  // for (unsigned int i = 0; i < (1 << n); i++) {
  //   cout << small_f[i] << " ";
  // }
  // cout << endl;

  // for (unsigned int i = 0; i < (1 << n); i++) {
  //   cout << big_f[i] << " ";
  // }
  // cout << endl;

  final(small_f, big_f, n, is_big, 0);
  // final(small_f, big_f, n, is_big, 0);
  // // final(small_f, big_f, n, is_big, 0);

  // for (unsigned int i = 0; i < (1 << n); i++) {
  //   cout << small_f[i] << " ";
  // }
  // cout << endl;

  // for (unsigned int i = 0; i < (1 << n); i++) {
  //   cout << big_f[i] << " ";
  // }
  // cout << endl;

  for (unsigned int i = 0; i < (1 << n); i++) {
    if (is_big[i]) {
      cout << small_f[i] << " ";
    } else {
      cout << big_f[i] << " ";
    }
  }
  cout << endl;

  delete small_f, big_f, is_big;

  // unsigned int a = 0, b = 1;
  // cout << (a & ~b) << endl;

  return 0;
}
