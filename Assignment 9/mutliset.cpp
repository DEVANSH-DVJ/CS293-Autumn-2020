#include <iostream>
#include <set>

using namespace std;

int main() {
  multiset<int> x;
  for (int i = 0; i < 5; i++) {
    x.insert(i);
  }

  for (auto i : x) {
    cout << i << " ";
  }
  cout << "\n";

  multiset<int>::iterator low, up;
  int n = ;
  low = x.lower_bound(n);
  up = x.upper_bound(n);

  cout << (low == x.begin()) << " " << (x.end() == low) << endl;
  cout << (up == x.begin()) << " " << (x.end() == up) << endl;

  return 0;
}
