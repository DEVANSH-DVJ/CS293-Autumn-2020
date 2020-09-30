#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  ifstream infile(argv[1]), outfile(argv[2]);
  int n, k, m, q, r;
  infile >> n >> k;
  vector<int> bag(k);
  for (int i = 0; i < k; i++)
    infile >> bag[i];
  while (outfile >> m) {
    // cout << "Current move " << m << endl;
    // for (int i = 0; i < k; i++) cout << bag[i] << " ";
    // cout << endl;
    q = bag[m] / k;
    r = bag[m] % k;
    bag[m] = q;
    for (int i = 1; i < k; i++)
      bag[(m + i) % k] += q;
    for (int i = 1; i <= r; i++)
      bag[(m + i) % k]++;
  }
  bool flag = true;
  q = n / k;
  for (int i = 0; (i < k) && flag; i++)
    if ((bag[i] < q) || (bag[i] > q + 1))
      flag = false;
  if (flag) {
    cout << "Correct\n";
    return 0;
  } else {
    cout << "Wrong\n";
    return 1;
  }
}
