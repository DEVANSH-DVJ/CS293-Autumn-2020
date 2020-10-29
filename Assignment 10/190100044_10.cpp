#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int n;

int bit_to_num(int *bit) {
  int num = 0;
  int x = 1;
  for (int i = n - 1; i >= 0; i--, x *= 2) {
    num += (x * bit[i]);
  }
  return num;
}

int *num_to_bit(int num) {
  int *bit = new int[n];
  int i = n - 1;
  while (num) {
    bit[i] = (num % 2);
    num /= 2;
    i--;
  }
  for (int j = i; j >= 0; j--) {
    bit[j] = 0;
  }
  return bit;
}

bool check(string f, string g, int *pi) {
  char h[n];
  int *bit1, bit2[n], i, j, k;

  for (i = 0; i < (1 << n); i++) {
    bit1 = num_to_bit(i);
    for (j = 0; j < n; j++) {
      bit2[j] = bit1[pi[j]];
    }
    k = bit_to_num(bit2);
    if (f[i] != g[k])
      return false;
  }

  return true;
}

struct compare_first {
  bool operator()(pair<int, int> const &t1, pair<int, int> const &t2) const {
    return t1.first < t2.first;
  }
};

class Func {
public:
  string s;
  vector<int> cfs;
  vector<pair<int, int>> sorted_i;
  int index;

  Func(string str, int i) {
    s = str;
    index = i;
    init_cfs();
  }

  void init_cfs() {
    cfs.resize(n, 0);
    for (int i = 0; i < (1 << n); i++) {
      if (s[i] == '1') {
        int *bit = num_to_bit(i);
        for (int j = 0; j < n; j++) {
          if (bit[j]) {
            cfs[j]++;
          }
        }
      }
    }
    sorted_i.resize(n);
    for (int i = 0; i < n; i++) {
      sorted_i[i] = pair<int, int>(cfs[i], i);
    }
    sort(sorted_i.begin(), sorted_i.end(), compare_first());
  }

  void print_cfs() {
    for (int i = 0; i < n; i++) {
      cout << cfs[i] << " ";
    }
    cout << "\n";
  }
};

struct compare {
  bool operator()(Func const &t1, Func const &t2) const {
    for (int i = 0; i < n; i++) {
      if (t1.sorted_i[i].first < t2.sorted_i[i].first)
        return true;
      if (t1.sorted_i[i].first > t2.sorted_i[i].first)
        return false;
    }
    return t1.index < t2.index;
  }
};

bool sorted_i_equality(Func const &t1, Func const &t2) {
  for (int i = 0; i < n; i++) {
    if (t1.sorted_i[i].first != t2.sorted_i[i].first)
      return false;
  }
  return true;
}

bool equivalence(Func const &f, Func const &g) {
  int *pi = new int[n];
  vector<int> perm_f, perm_g, temp_f, temp_g;
  int last = f.sorted_i[0].first;
  temp_f.push_back(f.sorted_i[0].second);
  temp_g.push_back(g.sorted_i[0].second);
  for (int i = 1; i < n; i++) {
    if (last != f.sorted_i[i].first) {
      if (temp_f.size() == 1) {
        pi[temp_f[0]] = temp_g[0];
      } else {
        perm_f.insert(perm_f.end(), temp_f.begin(), temp_f.end());
        perm_g.insert(perm_g.end(), temp_g.begin(), temp_g.end());
      }
      temp_f.clear();
      temp_g.clear();
      last = f.sorted_i[i].first;
      temp_f.push_back(f.sorted_i[i].second);
      temp_g.push_back(g.sorted_i[i].second);
    } else {
      temp_f.push_back(f.sorted_i[i].second);
      temp_g.push_back(g.sorted_i[i].second);
    }
  }
  if (temp_f.size() == 1) {
    pi[temp_f[0]] = temp_g[0];
  } else {
    perm_f.insert(perm_f.end(), temp_f.begin(), temp_f.end());
    perm_g.insert(perm_g.end(), temp_g.begin(), temp_g.end());
  }

  sort(perm_g.begin(), perm_g.end());
  do {
    for (int i = 0; i < perm_f.size(); i++) {
      pi[perm_f[i]] = perm_g[i];
    }
    if (check(f.s, g.s, pi)) {
      return true;
    }
  } while (std::next_permutation(perm_g.begin(), perm_g.end()));

  delete pi;
  return false;
}

int get_distinct(list<Func> fs) {
  list<Func>::iterator it, jt;
  for (it = fs.begin(); it != fs.end(); it++) {
    jt = it;
    jt++;
    while (jt != fs.end()) {
      if (equivalence(*it, *jt)) {
        jt = fs.erase(jt);
      } else {
        jt++;
      }
    }
  }
  return fs.size();
}

int distinct(vector<Func> fs) {
  sort(fs.begin(), fs.end(), compare());
  vector<list<Func>> s;
  s.emplace_back();
  s.back().push_back(fs[0]);
  for (int i = 1; i < fs.size(); i++) {
    if (!sorted_i_equality(fs[i], fs[i - 1])) {
      s.emplace_back();
    }
    s.back().push_back(fs[i]);
  }
  int count = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i].size() == 1) {
      count++;
    } else {
      count += get_distinct(s[i]);
    }
  }
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int m;
  cin >> n >> m;

  if (n == 0) {
    string str;
    bool is_zero = false, is_one = false;
    for (int i = 0; i < m; i++) {
      cin >> str;
      if (str == "1")
        is_one = true;
      else if (str == "0")
        is_zero = true;
    }
    cout << int(is_zero) + int(is_one) << endl;
    return 0;
  }

  vector<Func> fs;
  string str;
  for (int i = 0; i < m; i++) {
    cin >> str;
    fs.push_back(Func(str, i));
  }

  cout << distinct(fs) << endl;

  return 0;
}
