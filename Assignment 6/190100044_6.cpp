#include <iostream>

using namespace std;

// print function
template <typename T> void display(T *a, int n) {
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  return;
}

// The nearest element to the left that is greater or equal
int *ge_left(int a[], int n) {
  int *l = new int[n];
  l[0] = -1;
  for (int i = 1; i < n; i++) {
    int j = i - 1;
    while ((j >= 0) && a[j] < a[i])
      j = l[j];
    l[i] = j;
  }

  return l;
}

// The nearest element to the right that is greater or equal
int *ge_right(int a[], int n) {
  int *l = new int[n];
  l[n - 1] = n;
  for (int i = n - 2; i > -1; i--) {
    int j = i + 1;
    while ((j < n) && a[j] < a[i])
      j = l[j];
    l[i] = j;
  }

  return l;
}

// The nearest element to the left that is greater
int *g_left(int a[], int n) {
  int *l = new int[n];
  l[0] = -1;
  for (int i = 1; i < n; i++) {
    int j = i - 1;
    while ((j >= 0) && a[j] <= a[i])
      j = l[j];
    l[i] = j;
  }

  return l;
}

// The nearest element to the right that is less
int *l_right(int a[], int n) {
  int *l = new int[n];
  l[n - 1] = n;
  for (int i = n - 2; i > -1; i--) {
    int j = i + 1;
    while ((j < n) && a[j] >= a[i])
      j = l[j];
    l[i] = j;
  }

  return l;
}

// Part one - Societies in control of that building
long long int *first_part(int *ge_l, int *ge_r, int n) {
  long long int *ns = new long long int[n];

  for (int i = 0; i < n; i++) {
    ns[i] = (i - ge_l[i]) * (ge_r[i] - i);
  }

  return ns;
}

// Part two - total number of well-formed societies
long long int second_part(int *g_l, int *l_r, int n) {
  long long int count = n;

  long long int store = 0;
  int up_bound = l_r[0];
  for (int j = 1; j < up_bound; j++) {
    if (g_l[j] >= 0)
      continue;
    store++;
  }
  count += store;
  for (int i = 1; i < n - 1; i++) {
    if (l_r[i] != l_r[i - 1]) {
      store = 0;
      int up_bound = l_r[i];
      for (int j = i + 1; j < up_bound; j++) {
        if (g_l[j] >= i)
          continue;
        store++;
      }
    } else {
      store--;
    }
    count += store;
  }

  // for (int i = 0; i < n - 1; i++) {
  //   int up_bound = l_r[i];
  //   for (int j = i + 1; j < up_bound; j++) {
  //     if (g_l[j] >= i)
  //       continue;
  //     count++;
  //   }
  // }
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  int f[n];
  for (int i = 0; i < n; i++) {
    cin >> f[i];
  }

  int *ge_l = ge_left(f, n);
  // display<int>(ge_l, n);
  int *ge_r = ge_right(f, n);
  // display<int>(ge_r, n);

  long long int *ns = first_part(ge_l, ge_r, n);
  display<long long int>(ns, n);

  int *g_l = g_left(f, n);
  // display<int>(g_l, n);
  int *l_r = l_right(f, n);
  // display<int>(l_r, n);

  cout << second_part(g_l, l_r, n) << endl;

  delete ge_l, ge_r, g_l, l_r, ns;

  return 0;
}
