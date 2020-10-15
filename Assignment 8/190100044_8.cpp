#include <iostream>
#include <stack>
#include <string>

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

string infix(Node *t) {
  if (t->v == 'e') {
    return "e";
  } else {
    return "(" + infix(t->left) + t->v + infix(t->right) + ")";
  }
}

// int max(int n1, int n2) {
//   if (n1 > n2) {
//     return n1;
//   } else {
//     return n2;
//   }
// }

int first_steps(Node *t) {
  if (t->left->v == 'e') {
    if (t->right->v == 'e') {
      return 1;
    } else if (t->right->v == t->v) {
      return first_steps(t->right);
    } else {
      return first_steps(t->right) + 1;
    }
  } else if (t->left->v == t->v) {
    if (t->right->v == 'e') {
      return first_steps(t->left);
    } else if (t->right->v == t->v) {
      return first_steps(t->left) + first_steps(t->right) - 1;
    } else {
      return first_steps(t->left) + first_steps(t->right);
    }
  } else {
    if (t->right->v == 'e') {
      return first_steps(t->left) + 1;
    } else if (t->right->v == t->v) {
      return first_steps(t->left) + first_steps(t->right);
    } else {
      return first_steps(t->left) + first_steps(t->right) + 1;
    }
  }
}

int first_time(Node *t) {
  if (t->left->v == 'e') {
    if (t->right->v == 'e') {
      return 1;
    } else if (t->right->v == t->v) {
      return first_time(t->right);
    } else {
      return first_time(t->right) + 1;
    }
  } else if (t->left->v == t->v) {
    if (t->right->v == 'e') {
      return first_time(t->left);
    } else if (t->right->v == t->v) {
      return max(first_time(t->left), first_time(t->right));
    } else {
      return max(first_time(t->left), first_time(t->right) + 1);
    }
  } else {
    if (t->right->v == 'e') {
      return first_time(t->left) + 1;
    } else if (t->right->v == t->v) {
      return max(first_time(t->left) + 1, first_time(t->right));
    } else {
      return max(first_time(t->left) + 1, first_time(t->right) + 1);
    }
  }
}

// int *general_steps2(Node *t, int k) {
//   int ns, no;
//   if (t->left->v == 'e') {
//     if (t->right->v == 'e') {
//       ns = 1;
//       no = 2;
//     } else if (t->right->v == t->v) {
//       int *nr = general_steps2(t->right, k);
//       if (nr[1] + 1 > k) {
//         ns = nr[0] + 1;
//         no = 2;
//       } else {
//         ns = nr[0];
//         no = nr[1] + 1;
//       }
//     } else {
//       int *nr = general_steps2(t->right, k);
//       ns = nr[0] + 1;
//       no = 2;
//     }
//   } else if (t->left->v == t->v) {
//     if (t->right->v == 'e') {
//       int *nl = general_steps2(t->left, k);
//       if (nl[1] + 1 > k) {
//         ns = nl[0] + 1;
//         no = 2;
//       } else {
//         ns = nl[0];
//         no = nl[1] + 1;
//       }
//     } else if (t->right->v == t->v) {
//       int *nl = general_steps2(t->left, k);
//       int *nr = general_steps2(t->right, k);
//       if (nl[1] + nr[1] > k) {
//         if (nl[1] > nr[1]) {
//           if (nr[1] + 1 > k) {
//             ns = nl[0] + nr[0] + 1;
//             no = 2;
//           } else {
//             ns = nl[0] + nr[0];
//             no = nr[1] + 1;
//           }
//         } else {
//           if (nl[1] + 1 > k) {
//             ns = nl[0] + nr[0] + 1;
//             no = 2;
//           } else {
//             ns = nl[0] + nr[0];
//             no = nl[1] + 1;
//           }
//         }
//       } else {
//         ns = nl[0] + nr[0] - 1;
//         no = nl[1] + nr[1];
//       }
//     } else {
//       int *nl = general_steps2(t->left, k);
//       int *nr = general_steps2(t->right, k);
//       if (nl[1] + 1 > k) {
//         ns = nl[0] + nr[0] + 1;
//         no = 2;
//       } else {
//         ns = nl[0] + nr[0];
//         no = nl[1] + 1;
//       }
//     }
//   } else {
//     if (t->right->v == 'e') {
//       int *nl = general_steps2(t->right, k);
//       ns = nl[0] + 1;
//       no = 2;
//     } else if (t->right->v == t->v) {
//       int *nl = general_steps2(t->left, k);
//       int *nr = general_steps2(t->right, k);
//       if (nr[1] + 1 > k) {
//         ns = nl[0] + nr[0] + 1;
//         no = 2;
//       } else {
//         ns = nl[0] + nr[0];
//         no = nr[1] + 1;
//       }
//     } else {
//       int *nl = general_steps2(t->left, k);
//       int *nr = general_steps2(t->right, k);
//       ns = nl[0] + nr[0] + 1;
//       no = 2;
//     }
//   }

//   int *res = new int[2]{ns, no};
//   return res;
// }

int *general_steps(Node *t, int k) {
  int ns, no, *nl, *nr;
  int c;

  if (t->left->v != 'e') {
    nl = general_steps(t->left, k);
  } else {
    nl = new int[2]{0, 1};
  }

  if (t->right->v != 'e') {
    nr = general_steps(t->right, k);
  } else {
    nr = new int[2]{0, 1};
  }

  if (t->left->v == 'e') {
    if (t->right->v == 'e') {
      c = 0;
    } else if (t->right->v == t->v) {
      if (nr[1] + 1 > k) {
        c = 0;
      } else {
        c = 2;
      }
    } else {
      c = 0;
    }
  } else if (t->left->v == t->v) {
    if (t->right->v == 'e') {
      if (nl[1] + 1 > k) {
        c = 0;
      } else {
        c = 1;
      }
    } else if (t->right->v == t->v) {
      if (nl[1] + nr[1] > k) {
        if (nl[1] > nr[1]) {
          if (nr[1] + 1 > k) {
            c = 0;
          } else {
            c = 2;
          }
        } else {
          if (nl[1] + 1 > k) {
            c = 0;
          } else {
            c = 1;
          }
        }
      } else {
        c = 3;
      }
    } else {
      if (nl[1] + 1 > k) {
        c = 0;
      } else {
        c = 1;
      }
    }
  } else {
    if (t->right->v == 'e') {
      c = 0;
    } else if (t->right->v == t->v) {
      if (nr[1] + 1 > k) {
        c = 0;
      } else {
        c = 2;
      }
    } else {
      c = 0;
    }
  }

  switch (c) {
  case 0:
    ns = nl[0] + nr[0] + 1;
    no = 2;
    break;
  case 1:
    ns = nl[0] + nr[0];
    no = nl[1] + 1;
    break;
  case 2:
    ns = nl[0] + nr[0];
    no = nr[1] + 1;
    break;
  case 3:
    ns = nl[0] + nr[0] - 1;
    no = nl[1] + nr[1];
    break;
  }

  delete nl, nr;
  int *res = new int[2]{ns, no};
  return res;
}

int *general_time(Node *t, int k) {
  int nt, no, *nl, *nr;
  int c;

  if (t->left->v != 'e') {
    nl = general_time(t->left, k);
  } else {
    nl = new int[2]{0, 1};
  }

  if (t->right->v != 'e') {
    nr = general_time(t->right, k);
  } else {
    nr = new int[2]{0, 1};
  }

  if (t->left->v == 'e') {
    if (t->right->v == 'e') {
      c = 0;
    } else if (t->right->v == t->v) {
      if (nr[1] + 1 > k) {
        c = 0;
      } else {
        c = 2;
      }
    } else {
      c = 0;
    }
  } else if (t->left->v == t->v) {
    if (t->right->v == 'e') {
      if (nl[1] + 1 > k) {
        c = 0;
      } else {
        c = 1;
      }
    } else if (t->right->v == t->v) {
      if (nl[1] + nr[1] > k) {
        if (nl[1] > nr[1]) {
          if (nr[1] + 1 > k) {
            c = 0;
          } else {
            c = 2;
          }
        } else {
          if (nl[1] + 1 > k) {
            c = 0;
          } else {
            c = 1;
          }
        }
      } else {
        c = 3;
      }
    } else {
      if (nl[1] + 1 > k) {
        c = 0;
      } else {
        c = 1;
      }
    }
  } else {
    if (t->right->v == 'e') {
      c = 0;
    } else if (t->right->v == t->v) {
      if (nr[1] + 1 > k) {
        c = 0;
      } else {
        c = 2;
      }
    } else {
      c = 0;
    }
  }

  switch (c) {
  case 0:
    nt = max(nl[0] + 1, nr[0] + 1);
    no = 2;
    break;
  case 1:
    nt = max(nl[0], nr[0] + 1);
    if (nl[0] < nr[0] + 1) {
      no = 2;
    } else {
      no = nl[1] + 1;
    }
    break;
  case 2:
    nt = max(nl[0] + 1, nr[0]);
    if (nr[0] < nl[0] + 1) {
      no = 2;
    } else {
      no = nr[1] + 1;
    }
    break;
  case 3:
    nt = max(nl[0], nr[0]);
    if (nr[0] < nl[0]) {
      no = nl[1] + 1;
    } else if (nl[0] < nr[0]) {
      no = nr[1] + 1;
    } else {
      no = nl[1] + nr[1];
    }
    break;
  }

  delete nl, nr;
  int *res = new int[2]{nt, no};
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string postfix;
  cin >> postfix;
  int t;
  cin >> t;
  int k[t];
  for (int i = 0; i < t; i++) {
    cin >> k[i];
  }

  Node *root = expressionTree(postfix);
  // cout << infix(root) << endl;
  // cout << first_steps(root) << " " << first_time(root) << endl;
  cout << general_steps(root, (postfix.length() - 1) / 2)[0] << " "
       << first_time(root) << endl;

  for (int i = 0; i < t; i++) {
    cout << general_steps(root, k[i])[0] << " " << general_time(root, k[i])[0]
         << endl;
  }

  return 0;
}