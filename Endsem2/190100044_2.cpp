#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  char v;
  Node *left;
  Node *right;

  Node(char s) {
    v = s;
    left = NULL;
    right = NULL;
  }
};

Node *expressionTree(string postfix) {
  stack<Node *> st;
  Node *t, *tl, *tr;

  for (int i = 0; i < postfix.length(); i++) {
    if (postfix[i] == 'e') {
      t = new Node(postfix[i]);
      st.push(t);
    } else {
      t = new Node(postfix[i]);
      tr = st.top();
      st.pop();
      tl = st.top();
      st.pop();

      t->right = tr;
      t->left = tl;

      st.push(t);
    }
  }

  t = st.top();
  st.pop();

  return t;
}

long long int count_edges;

long long int solve(Node *t, int &path, vector<int> &separate_paths) {
  if (t->v == 'e') {
    path = 0;
    separate_paths.push_back(0);
    return 1;
  } else {
    int left_path, right_path;
    vector<int> left_separate_paths, right_separate_paths;
    long long int left_desc = solve(t->left, left_path, left_separate_paths);
    long long int right_desc =
        solve(t->right, right_path, right_separate_paths);

    if (t->v == '1') {
      count_edges += (left_desc * right_desc);
      path = 0;

      int diff = left_desc - right_desc;
      if (diff == 0 || diff == 1 || diff == -1) {
        path = left_desc + right_desc - 1;
        separate_paths.push_back(path);
      } else if (diff > 1) {
        if (left_separate_paths.size() <= right_desc + 1) {
          path = left_desc + right_desc - 1;
          separate_paths.push_back(path);
        } else { // left_separate_paths.size() > right_desc + 1
          int i;
          for (i = 0; i <= right_desc; i++) {
            path += left_separate_paths[i];
          }
          path += 2 * right_desc;

          separate_paths.push_back(path);
          for (; i < left_separate_paths.size(); i++) {
            separate_paths.push_back(left_separate_paths[i]);
          }
        }
      } else { // diff < -1
        if (right_separate_paths.size() <= left_desc + 1) {
          path = right_desc + left_desc - 1;
          separate_paths.push_back(path);
        } else { // right_separate_paths.size() > left_desc + 1
          int i;
          for (i = 0; i <= left_desc; i++) {
            path += right_separate_paths[i];
          }
          path += 2 * left_desc;

          separate_paths.push_back(path);
          for (; i < right_separate_paths.size(); i++) {
            separate_paths.push_back(right_separate_paths[i]);
          }
        }
      }
    } else {
      path = max(left_path, right_path);

      int i = 0, j = 0;
      while (i < left_separate_paths.size() &&
             j < right_separate_paths.size()) {
        if (left_separate_paths[i] >= right_separate_paths[j]) {
          separate_paths.push_back(left_separate_paths[i]);
          i++;
        } else {
          separate_paths.push_back(right_separate_paths[j]);
          j++;
        }
      }

      while (i < left_separate_paths.size()) {
        separate_paths.push_back(left_separate_paths[i]);
        i++;
      }

      while (j < right_separate_paths.size()) {
        separate_paths.push_back(right_separate_paths[j]);
        j++;
      }
    }
    return left_desc + right_desc;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string postfix;
  cin >> postfix;

  Node *root = expressionTree(postfix);

  count_edges = 0;
  int path;
  vector<int> separate_paths;
  solve(root, path, separate_paths);
  cout << count_edges << endl;
  cout << path << endl;

  return 0;
}
