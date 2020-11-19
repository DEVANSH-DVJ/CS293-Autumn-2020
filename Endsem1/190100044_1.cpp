#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  int seq[n];
  int freq[n];

  for (int i = 0; i < n; i++) {
    freq[i] = 0;
  }

  int x;
  for (int i = 0; i < n; i++) {
    cin >> x;
    seq[i] = x;
    freq[x]++;
  }

  int maximum = 0, majority;
  for (int i = 0; i < n; i++) {
    if (freq[i] > maximum) {
      maximum = freq[i];
      majority = i;
    }
  }

  if (2 * maximum - 1 > n) {
    cout << n << endl;
  } else {
    cout << 2 * maximum - 1 << endl;
  }

  return 0;
}
