#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 100000, m = 100000;
  set<pair<int, int>> s;
  int u = rand() % n, v = rand() % n;
  cout << n << ' ' << m << ' ' << u << ' ' << v << endl;
  while (m--) {
    int a = rand() % n, b = rand() % n;
    if (a > b)
      swap(a, b);
    while (a >= b || s.find(make_pair(a, b)) != s.end()) {
      a = rand() % n, b = rand() % n;
      if (a > b)
        swap(a, b);
    }
    s.insert(make_pair(a, b));
    cout << a << ' ' << b << '\n';
  }
  return 0;
}
