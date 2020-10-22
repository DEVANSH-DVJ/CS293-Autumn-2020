#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

bool uniq = true;

struct p {
  int first;
  int second;
  int index;
};

struct compare_first {
  bool operator()(p const &t1, p const &t2) const {
    if (t1.first == t2.first) {
      return t1.second < t2.second;
    }
    return t1.first < t2.first;
  }
};

struct compare_second {
  bool operator()(p const &t1, p const &t2) const {
    return t1.second < t2.second;
  }
};

int main() {
  int n;
  cin >> n;
  vector<multiset<p, compare_second>> S[2];
  vector<p> store[2]; // Stores the initial input

  for (int i = 0; i < 2; i++) {
    vector<p> in(n);
    for (int j = 0; j < n; j++) {
      cin >> in[j].first;
    }
    for (int j = 0; j < n; j++) {
      cin >> in[j].second;
      in[j].index = j + 1;
    }
    for (int j = 0; j < n; j++) {
      store[i].push_back(in[j]);
    }
    sort(in.begin(), in.end(), compare_first());
    for (int j = 0; j < n; j++) {
      if (j == 0 || in[j - 1].first != in[j].first) {
        S[i].emplace_back();
      }
      S[i].back().insert(in[j]);
    }
  }

  // for (int i = 0; i < 2; i++) {
  //   for (auto j : S[i]) {
  //     for (auto k : j) {
  //       cout << "(" << k.first << "," << k.second << "," << k.index << ")"
  //            << "//";
  //     }
  //     cout << ";;";
  //   }
  //   cout << endl;
  //   for (auto j : store[i]) {
  //     cout << "(" << j.first << "," << j.second << ")"
  //          << "//";
  //   }
  //   cout << endl;
  // }

  vector<p> final[2]; // Stores the initial input
  vector<int> ret[2];
  for (int i0 = 0, i1 = 0; ret[0].size() < n;) {
    if (S[0][i0].size() < S[1][i1].size()) {
      if (S[0][i0].size() > 1) {
        uniq = false;
      }
      for (auto const &t : S[0][i0]) {
        auto it = S[1][i1].upper_bound(t);
        if (it == S[1][i1].begin()) {
          cout << "impossible" << endl;
          return 0;
        }
        --it;
        ret[0].push_back(t.index);
        ret[1].push_back(it->index);
        final[0].push_back(t);
        final[1].push_back(*it);
        S[1][i1].erase(it);
      }
      i0++;
    } else {
      if (S[1][i1].size() > 1) {
        uniq = false;
      }
      for (auto const &t : S[1][i1]) {
        auto it = S[0][i0].lower_bound(t);
        if (it == S[0][i0].end()) {
          cout << "impossible" << endl;
          return 0;
        }
        ret[1].push_back(t.index);
        ret[0].push_back(it->index);
        final[1].push_back(t);
        final[0].push_back(*it);
        S[0][i0].erase(it);
      }
      i1++;
      if (S[0][i0].size() == 0)
        i0++;
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      cout << ret[i][j] << " ";
    }
    cout << endl;
  }

  // for (int i = 0; i < 2; i++) {
  //   for (auto j : final[i]) {
  //     cout << "(" << j.first << "," << j.second << ")"
  //          << "//";
  //   }
  //   cout << endl;
  // }

  if (uniq) {
    p a, b, c, d;
    for (int i = 0; i < n - 1; i++) {
      a = final[0][i];
      b = final[0][i + 1];
      c = final[1][i];
      d = final[1][i + 1];
      if (a.first == b.first || c.first == d.first) {
        if (a.second >= d.second && b.second >= c.second) {
          cout << "not unique"
               << "\n";
          return 0;
        }
      }
    }
    cout << "unique"
         << "\n";
    return 0;

  } else {
    cout << "not unique"
         << "\n";
    return 0;
  }
}
