#include <iostream>
#include <list>
#include <queue>
// #include <set>
#include <unordered_set>
// #include <vector>

using namespace std;

struct EdgeData {
  list<int>::iterator uinv, vinu;
  int indep[4]{0, 0, 0, 0};
  bool orig = true;
};

class Edge {
public:
  int u, v;
  EdgeData *data;

  Edge(int u, int v) {
    this->u = u;
    this->v = v;
    data = new EdgeData();
  }

  bool operator==(const Edge &obj) const {
    if (u == obj.u && v == obj.v) {
      return true;
    } else {
      return false;
    }
  }
};

namespace std {
template <> struct hash<Edge> {
  size_t operator()(const Edge &obj) const {
    return hash<long long>()((long long)obj.u * 100000LL + (long long)obj.v);
  }
};
} // namespace std

class Graph {
public:
  int n, m;
  int del_count = 0;
  // vector<bool> is_del;
  list<int> *adj;
  unordered_set<Edge> E;
  queue<int> reducible;
  int *inc, *exc;

  Graph() {
    cin >> n >> m;
    // is_del.resize(n, false);
    adj = new list<int>[n];
    inc = new int[n]; // Inclusive
    exc = new int[n]; // Exclusive
    for (int i = 0; i < n; i++) {
      inc[i] = 0;
      exc[i] = 0;
    }

    int u, v;
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      Edge e = u < v ? Edge(u, v) : Edge(v, u);
      pair<unordered_set<Edge>::iterator, bool> res = E.insert(e);
      if (res.second) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        res.first->data->uinv = adj[v].end();
        res.first->data->uinv--;
        res.first->data->vinu = adj[u].end();
        res.first->data->vinu--;
        // it->data->inc = i;
      } else {
        // Edge already existed
      }
    }
    // for (auto it : E) {
    //   cout << it.data->inc << endl;
    // }
  }

  int reduce() {
    for (int i = 0; i < n; i++) {
      if (adj[i].size() <= 2) {
        reducible.push(i);
      }
    }

    while (del_count < n - 1 && reducible.size() != 0) {
      // cout << del_count << endl;
      int u = reducible.front();
      reducible.pop();

      if (adj[u].size() == 0) {
        continue;
      } else if (adj[u].size() == 1) {
        int v = adj[u].front();
        Edge e = u < v ? Edge(u, v) : Edge(v, u);
        unordered_set<Edge>::iterator it = E.find(e);
        adj[v].erase(it->data->uinv);
        adj[u].erase(it->data->vinu);
        if (adj[v].size() == 2) {
          reducible.push(v);
        }

        // inc[v]
        if (it->data->orig) {
          if (u < v)
            inc[v] += it->data->indep[2] + exc[u];
          else
            inc[v] += it->data->indep[1] + exc[u];
        } else {
          if (u < v)
            inc[v] += max(it->data->indep[0] + inc[u] + 1,
                          it->data->indep[2] + exc[u]);
          else
            inc[v] += max(it->data->indep[0] + inc[u] + 1,
                          it->data->indep[1] + exc[u]);
        }

        // exc[v]
        if (u < v)
          exc[v] +=
              max(it->data->indep[1] + inc[u] + 1, it->data->indep[3] + exc[u]);
        else
          exc[v] +=
              max(it->data->indep[2] + inc[u] + 1, it->data->indep[3] + exc[u]);

        E.erase(it);
        del_count++; // Degree of u is zero.
      } else if (adj[u].size() == 2) {
        int v = adj[u].front();
        int w = *std::next(adj[u].begin());
        unordered_set<Edge>::iterator it, jt;

        it = u < v ? E.find(Edge(u, v)) : E.find(Edge(v, u));
        adj[v].erase(it->data->uinv);
        adj[u].erase(it->data->vinu);

        jt = u < w ? E.find(Edge(u, w)) : E.find(Edge(w, u));
        adj[w].erase(jt->data->uinv);
        adj[u].erase(jt->data->vinu);

        Edge e = v < w ? Edge(v, w) : Edge(w, v);
        pair<unordered_set<Edge>::iterator, bool> res = E.insert(e);
        if (res.second) {
          adj[v].push_back(w);
          adj[w].push_back(v);
          res.first->data->uinv = adj[w].end();
          res.first->data->uinv--;
          res.first->data->vinu = adj[v].end();
          res.first->data->vinu--;
          res.first->data->orig = false;
        } else {
          // Edge already existed
        }

        if (adj[v].size() == 2) {
          reducible.push(v);
        }
        if (adj[w].size() == 2) {
          reducible.push(w);
        }

        // res.first->data->indep[0]
        if (!res.first->data->orig) {
          if (it->data->orig || jt->data->orig) {
            if (u < v && u < w) {
              res.first->data->indep[0] +=
                  it->data->indep[2] + jt->data->indep[2] + exc[u];
            } else if (u > v && v < w) {
              res.first->data->indep[0] +=
                  it->data->indep[1] + jt->data->indep[2] + exc[u];
            } else if (u < v && v > w) {
              res.first->data->indep[0] +=
                  it->data->indep[2] + jt->data->indep[1] + exc[u];
            } else { // u > v, u > w
              res.first->data->indep[0] +=
                  it->data->indep[1] + jt->data->indep[1] + exc[u];
            }
          } else {
            if (u < v && u < w) {
              res.first->data->indep[0] +=
                  max(it->data->indep[0] + jt->data->indep[0] + inc[u] + 1,
                      it->data->indep[2] + jt->data->indep[2] + exc[u]);
            } else if (u > v && v < w) {
              res.first->data->indep[0] +=
                  max(it->data->indep[0] + jt->data->indep[0] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[2] + exc[u]);
            } else if (u < v && v > w) {
              res.first->data->indep[0] +=
                  max(it->data->indep[0] + jt->data->indep[0] + inc[u] + 1,
                      it->data->indep[2] + jt->data->indep[1] + exc[u]);
            } else { // u > v, u > w
              res.first->data->indep[0] +=
                  max(it->data->indep[0] + jt->data->indep[0] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[1] + exc[u]);
            }
          }
        }

        if (v < w) {
          // res.first->data->indep[1]
          if (it->data->orig) {
            if (u < v) { // u < w
              res.first->data->indep[1] +=
                  it->data->indep[2] + jt->data->indep[3] + exc[u];
            } else if (u < w) { // u > v
              res.first->data->indep[1] +=
                  it->data->indep[1] + jt->data->indep[3] + exc[u];
            } else { // u > v, u > w
              res.first->data->indep[1] +=
                  it->data->indep[1] + jt->data->indep[3] + exc[u];
            }
          } else {
            if (u < v) { // u < w
              res.first->data->indep[1] +=
                  max(it->data->indep[0] + jt->data->indep[1] + inc[u] + 1,
                      it->data->indep[2] + jt->data->indep[3] + exc[u]);
            } else if (u < w) { // u > v
              res.first->data->indep[1] +=
                  max(it->data->indep[0] + jt->data->indep[1] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[3] + exc[u]);
            } else { // u > v, u > w
              res.first->data->indep[1] +=
                  max(it->data->indep[0] + jt->data->indep[2] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[3] + exc[u]);
            }
          }
          // res.first->data->indep[2]
          if (jt->data->orig) {
            if (u < w) { // u < v
              res.first->data->indep[2] +=
                  jt->data->indep[2] + it->data->indep[3] + exc[u];
            } else if (u < v) { // u > w
              res.first->data->indep[2] +=
                  jt->data->indep[1] + it->data->indep[3] + exc[u];
            } else { // u > w, u > v
              res.first->data->indep[2] +=
                  jt->data->indep[1] + it->data->indep[3] + exc[u];
            }
          } else {
            if (u < w) { // u < v
              res.first->data->indep[2] +=
                  max(jt->data->indep[0] + it->data->indep[1] + inc[u] + 1,
                      jt->data->indep[2] + it->data->indep[3] + exc[u]);
            } else if (u < v) { // u > w
              res.first->data->indep[2] +=
                  max(jt->data->indep[0] + it->data->indep[1] + inc[u] + 1,
                      jt->data->indep[1] + it->data->indep[3] + exc[u]);
            } else { // u > w, u > v
              res.first->data->indep[2] +=
                  max(jt->data->indep[0] + it->data->indep[2] + inc[u] + 1,
                      jt->data->indep[1] + it->data->indep[3] + exc[u]);
            }
          }
        } else {
          // res.first->data->indep[2]
          if (it->data->orig) {
            if (u < v) { // u < w
              res.first->data->indep[2] +=
                  it->data->indep[2] + jt->data->indep[3] + exc[u];
            } else if (u < w) { // u > v
              res.first->data->indep[2] +=
                  it->data->indep[1] + jt->data->indep[3] + exc[u];
            } else { // u > v, u > w
              res.first->data->indep[2] +=
                  it->data->indep[1] + jt->data->indep[3] + exc[u];
            }
          } else {
            if (u < v) { // u < w
              res.first->data->indep[2] +=
                  max(it->data->indep[0] + jt->data->indep[1] + inc[u] + 1,
                      it->data->indep[2] + jt->data->indep[3] + exc[u]);
            } else if (u < w) { // u > v
              res.first->data->indep[2] +=
                  max(it->data->indep[0] + jt->data->indep[1] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[3] + exc[u]);
            } else { // u > v, u > w
              res.first->data->indep[2] +=
                  max(it->data->indep[0] + jt->data->indep[2] + inc[u] + 1,
                      it->data->indep[1] + jt->data->indep[3] + exc[u]);
            }
          }
          // res.first->data->indep[1]
          if (jt->data->orig) {
            if (u < w) { // u < v
              res.first->data->indep[1] +=
                  jt->data->indep[2] + it->data->indep[3] + exc[u];
            } else if (u < v) { // u > w
              res.first->data->indep[1] +=
                  jt->data->indep[1] + it->data->indep[3] + exc[u];
            } else { // u > w, u > v
              res.first->data->indep[1] +=
                  jt->data->indep[1] + it->data->indep[3] + exc[u];
            }
          } else {
            if (u < w) { // u < v
              res.first->data->indep[1] +=
                  max(jt->data->indep[0] + it->data->indep[1] + inc[u] + 1,
                      jt->data->indep[2] + it->data->indep[3] + exc[u]);
            } else if (u < v) { // u > w
              res.first->data->indep[1] +=
                  max(jt->data->indep[0] + it->data->indep[1] + inc[u] + 1,
                      jt->data->indep[1] + it->data->indep[3] + exc[u]);
            } else { // u > w, u > v
              res.first->data->indep[1] +=
                  max(jt->data->indep[0] + it->data->indep[2] + inc[u] + 1,
                      jt->data->indep[1] + it->data->indep[3] + exc[u]);
            }
          }
        }

        // res.first->data->indep[3]
        if (u < v && u < w) {
          res.first->data->indep[3] += max(
              it->data->indep[1] + jt->data->indep[1] + inc[u] + 1,
              it->data->indep[3] + jt->data->indep[3] + max(inc[u], exc[0]));
        } else if (u > v && u < w) {
          res.first->data->indep[3] += max(
              it->data->indep[2] + jt->data->indep[1] + inc[u] + 1,
              it->data->indep[3] + jt->data->indep[3] + max(inc[u], exc[0]));
        } else if (u < v && u > w) {
          res.first->data->indep[3] += max(
              it->data->indep[1] + jt->data->indep[2] + inc[u] + 1,
              it->data->indep[3] + jt->data->indep[3] + max(inc[u], exc[0]));
        } else { // u > v, u > w
          res.first->data->indep[3] += max(
              it->data->indep[2] + jt->data->indep[2] + inc[u] + 1,
              it->data->indep[3] + jt->data->indep[3] + max(inc[u], exc[0]));
        }

        E.erase(it);
        E.erase(jt);
        del_count++; // Degree of u is zero.
      }
    }

    if (del_count == n - 1) {
      int v = reducible.front();
      return (inc[v] >= exc[v]) ? 1 + inc[v] : exc[v];
    } else {
      return -1;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Graph g;
  int max_ind = g.reduce();

  if (max_ind == -1) {
    cout << "no\n";
  } else {
    cout << "yes\n" << max_ind << "\n";
  }

  return 0;
}
