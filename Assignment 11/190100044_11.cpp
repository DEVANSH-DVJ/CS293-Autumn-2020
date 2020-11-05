#include <iostream>
#include <list>
#include <set>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

int maximum(int &x, int &y) {
  if (x > y)
    return x;
  else
    return y;
}

class Graph {
  int n, u, v;
  list<int> *adj;
  vector<int> dis_u, dis_v;

public:
  Graph(int n, int u, int v) {
    this->n = n;
    adj = new list<int>[2 * n];
    this->u = u;
    this->v = v;
  }

  void add(int x, int y) {
    adj[x].push_back(y + n);
    adj[y + n].push_back(x);
    adj[x + n].push_back(y);
    adj[y].push_back(x + n);
  }

  void shortestPath(int src, vector<int> &dist) {
    set<pair<int, int>> setds;

    dist.resize(2 * n, INF);

    setds.insert(make_pair(0, src));
    dist[src] = 0;

    while (!setds.empty()) {
      pair<int, int> tmp = *(setds.begin());
      setds.erase(setds.begin());

      int u = tmp.second;

      list<int>::iterator i;
      for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;

        if (dist[v] > dist[u] + 1) {
          if (dist[v] != INF)
            setds.erase(setds.find(make_pair(dist[v], v)));

          dist[v] = dist[u] + 1;
          setds.insert(make_pair(dist[v], v));
        }
      }
    }
  }

  void run() {
    shortestPath(this->u, dis_u);
    shortestPath(this->v, dis_v);

    int min = INF, minie, minio;
    list<int> min_list;

    for (int i = 0; i < n; ++i) {
      minie = maximum(dis_u[i], dis_v[i]);
      minio = maximum(dis_u[i + n], dis_v[i + n]);
      if (minie < min || minio < min) {
        if (minio < minie) {
          min = minio;
        } else {
          min = minie;
        }
        min_list.clear();
        min_list.push_back(i);
      } else {
        if (minie == min || minio == min) {
          min_list.push_back(i);
        }
      }
    }

    if (min == INF) {
      cout << "impossible\n";
    } else {
      cout << "possible\n" << min << "\n";
      for (auto i : min_list) {
        cout << i << " ";
      }
      cout << "\n";
    }
    return;
  }

  void test() {
    cout << "u = " << this->u << ", v = " << this->v;
    cout << "\nNode, Even dis from u, Odd dis from u, Even dis from v, Odd dis "
            "from v\n";
    for (int i = 0; i < n; ++i) {
      cout << i << ", " << dis_u[i] << ", " << dis_u[i + n] << ", " << dis_v[i]
           << ", " << dis_v[i + n] << "\n";
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
  // g.test();

  return 0;
}
