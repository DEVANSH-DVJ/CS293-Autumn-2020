#include <iostream>
#include <map>
#include <string>

using namespace std;

int primes[46] = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,
                  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                  97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
                  157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

int difference(string &s1, string &s2, int l) {
  int count = 0;
  for (int i = 0; i < l; i++) {
    if (s1[i] != s2[i])
      count++;
  }
  return count;
}

int replace_char(string &s, int k, int n) {
  if (k == 2) {
    int count = 0;
    int half = n / 2;
    for (int i = 0; i < half; i++) {
      if (s[i] != s[i + half])
        count++;
    }
    return count;
  }

  if (k == 3) {
    int count = 0;
    int third = n / 3;
    int two_third = 2 * third;
    for (int i = 0; i < third; i++) {
      bool ab = (s[i] == s[i + third]);
      bool ac = (s[i] == s[i + two_third]);
      bool bc = (s[i + third] == s[i + two_third]);
      if (ab && ac) {
        continue;
      } else if (ab || bc || ac) {
        count++;
      } else {
        count += 2;
      }
    }
    return count;
  }

  int subl = n / k;
  int count[subl][27];

  for (int i = 0; i < subl; i++) {
    for (int j = 0; j < 27; j++) {
      count[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    count[i % subl][(int(s[i]) - 97)]++;
  }

  int max[subl];
  int sim = 0;
  for (int i = 0; i < subl; i++) {
    max[i] = 0;
    for (int j = 0; j < 26; j++) {
      if (max[i] < count[i][j])
        max[i] = count[i][j];
    }
    sim += max[i];
  }

  return n - sim;
}

int add_char(string &s, int k, int n) {
  int op = 20000, op_temp;
  string con = "";
  for (int j = 0; j < k; j++)
    con += "{";
  int max = n - (n / k);
  for (int i = 0; i < max; i += k) {
    op_temp = replace_char(s, k, n + i);
    s += con;
    if (op > op_temp) {
      op = op_temp;
      if (op == i) {
        return i;
      }
    }
  }

  return op;
}

int add_replace_char(string &s, int n) {
  int op = 20000, op_temp;
  int k = 0, k_temp;
  for (int i = 0; i < 46; i++) {
    // cout << k_temp << endl;
    k_temp = primes[i];
    if (k_temp * k_temp > 2 * n)
      break;
    int rem = n % k_temp;
    if (rem == 0) {
      op_temp = add_char(s, k_temp, n);
    } else {
      string s_temp = s;
      for (int j = 0; j < k_temp - rem; j++)
        s_temp += "{";
      op_temp = add_char(s_temp, k_temp, n + k_temp - rem);
    }
    if (op > op_temp) {
      op = op_temp;
      k = k_temp;
      if (op == 0) {
        break;
      }
    }
  }
  cout << op << " ";

  return k;
}

// int replace_char(string &s, int k, int n) {
//   map<string, int[2]> sim;

//   for (int i = 0; i < n; i += k) {
//     sim[s.substr(i, k)][0] = 0;
//     sim[s.substr(i, k)][1] = 0;
//   }

//   for (int i = 0; i < n; i += k) {
//     sim[s.substr(i, k)][1]++;
//   }

//   for (int i = 0; i < n; i += k) {
//     string s1 = s.substr(i, k);
//     if (sim[s1][0] != 0)
//       continue;
//     for (int j = 0; j < n; j += k) {
//       string s2 = s.substr(j, k);
//       int diff = difference(s1, s2, k);
//       sim[s1][0] += diff;
//       // cout << s1 << "//" << s2 << "//" << diff << endl;
//     }
//   }

//   int min = n;
//   for (int i = 0; i < n; i += k) {
//     int *s0 = sim[s.substr(i, k)];
//     int c = s0[0];
//     if (min > c)
//       min = c;
//   }

//   return min;
// }

// int replace_char(string &s, int k, int n) {
//   map<string, int[2]> sim;

//   for (int i = 0; i < n; i += k) {
//     sim[s.substr(i, k)][0] = 0;
//     sim[s.substr(i, k)][1] = 0;
//   }

//   for (int i = 0; i < n; i +=k) {
//     sim[s.substr(i,k)][1]++;
//   }

//   for (int i = 0; i < n; i += k) {
//     string s1 = s.substr(i, k);
//     for (int j = i + k; j < n; j += k) {
//       string s2 = s.substr(j, k);
//       int diff = difference(s1, s2, k);
//       sim[s1][0] += diff;
//       sim[s2][0] += diff;
//       // cout << s1 << "//" << s2 << "//" << diff << endl;
//     }
//   }

//   int min = n;
//   for (int i = 0; i < n; i += k) {
//     int *s0 = sim[s.substr(i, k)];
//     int c = s0[0]/s0[1];
//     if (min > c)
//       min = c;
//   }

//   return min;
// }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  int k;
  getline(cin, s);
  cin >> k;

  int n = s.length();

  if (n == 0) {
    cout << 0 << endl << "0 0" << endl;
    return 0;
  }

  cout << replace_char(s, k, n) << endl;
  cout << add_replace_char(s, n) << endl;

  return 0;
}
