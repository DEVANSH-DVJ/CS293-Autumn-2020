#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
  int n, u, v;
  list<int> *adj;
  vector<int> dis_o_u, dis_e_u, dis_o_v, dis_e_v;

public:
  Graph(int n, int u, int v) {
    this->n = n;
    adj = new list<int>[n];
    this->u = u;
    this->v = v;
    dis_o_u.resize(n, -1);
    dis_e_u.resize(n, -1);
    dis_o_v.resize(n, -1);
    dis_e_v.resize(n, -1);
  }

  void add(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  void dfs_oe(int x, bool is_even, bool wrt_u) {
    if (wrt_u) {
      if (is_even) {
        for (auto y : adj[x]) {
          if (dis_o_u[y] == -1 || dis_o_u[y] > dis_e_u[x] + 1) {
            dis_o_u[y] = dis_e_u[x] + 1;
            dfs_oe(y, !is_even, wrt_u);
          }
        }
      } else {
        for (auto y : adj[x]) {
          if (dis_e_u[y] == -1 || dis_e_u[y] > dis_o_u[x] + 1) {
            dis_e_u[y] = dis_o_u[x] + 1;
            dfs_oe(y, !is_even, wrt_u);
          }
        }
      }
    } else {
      if (is_even) {
        for (auto y : adj[x]) {
          if (dis_o_v[y] == -1 || dis_o_v[y] > dis_e_v[x] + 1) {
            dis_o_v[y] = dis_e_v[x] + 1;
            dfs_oe(y, !is_even, wrt_u);
          }
        }
      } else {
        for (auto y : adj[x]) {
          if (dis_e_v[y] == -1 || dis_e_v[y] > dis_o_v[x] + 1) {
            dis_e_v[y] = dis_o_v[x] + 1;
            dfs_oe(y, !is_even, wrt_u);
          }
        }
      }
    }
  }

  void run() {
    dis_e_u[this->u] = 0;
    dfs_oe(this->u, true, true);
    dis_e_v[this->v] = 0;
    dfs_oe(this->v, true, false);

    // int min = 0;
    // list<int> min_dis;
  }

  void test() {
    cout << "u = " << this->u << ", v = " << this->v;
    cout << "\nNode, Even dis from u, Odd dis from u, Even dis from v, Odd dis "
            "from v\n";
    for (int i = 0; i < n; ++i) {
      cout << i << ", " << dis_e_u[i] << ", " << dis_o_u[i] << ", "
           << dis_e_v[i] << ", " << dis_o_v[i] << "\n";
    }
    cout << endl;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, u, v;
  cin >> n >> m >> u >> v;

  Graph g(n, u, v);
  int x, y;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    g.add(x, y);
  }
  g.run();
  g.test();

  return 0;
}
