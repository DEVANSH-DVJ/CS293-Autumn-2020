#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string.h>
#include <vector>
using namespace std;

// bool string_less_than(string ch1, string ch2) { return (strcmp(ch1.c_str(),
// ch2.c_str()) < 0); }

class Course {
public:
  string name;
  int slot;
  int max_reg;
  list<string> students;

  Course(string ch, int slot_number, int max) {
    name = ch;
    max_reg = max;
    slot = slot_number;
  }

  // bool operator<(const Course &d) { return (strcmp(name, d.name) < 0); }
  bool operator<(const Course &d) { return name < d.name; }

  // ~Course() { delete name; }
};

class Student {
public:
  string name;
  int max_courses;
  list<string> courses;

  Student(string ch, int max) {
    name = ch;
    max_courses = max;
  }

  bool operator<(const Student &d) { return name < d.name; }

  // ~Student() { delete name; }
};

class Acad {
public:
  int courses_count, students_count, max_courses;
  vector<Course> courses;
  vector<Student> students;
  vector<string> courses_name;
  vector<string> students_name;

  Acad(int courses_count_, int students_count_, int max_courses_) {
    courses_count = courses_count_;
    students_count = students_count_;
    max_courses = max_courses_;

    char ch1[6];
    int c;
    int max;
    for (int i = 0; i < courses_count; i++) {
      cin >> ch1 >> c >> max;
      if (max == -1) {
        max = students_count;
      }
      courses.push_back(Course(ch1, c, max));
    }

    char ch2[9];
    for (int i = 0; i < students_count; i++) {
      cin >> ch2;
      Student a(ch2, max_courses);
      students.push_back(a);
    }

    sort(courses.begin(), courses.end());
    for (int i = 0; i < courses_count; i++) {
      courses_name.push_back(courses[i].name);
    }
    sort(students.begin(), students.end());
    for (int i = 0; i < students_count; i++) {
      students_name.push_back(students[i].name);
    }
  }

  void reg(string stu, string cou) {
    pair<vector<string>::iterator, vector<string>::iterator> student_indices;
    student_indices =
        equal_range(students_name.begin(), students_name.end(), stu);
    if (student_indices.first == student_indices.second) {
      cout << "fail\n";
      return;
    }

    pair<vector<string>::iterator, vector<string>::iterator> course_indices;
    course_indices = equal_range(courses_name.begin(), courses_name.end(), cou);
    if (course_indices.first == course_indices.second) {
      cout << "fail\n";
      return;
    }

    vector<Course>::iterator course_index =
        courses.begin() + (course_indices.first - courses_name.begin());
    vector<Student>::iterator student_index =
        students.begin() + (student_indices.first - students_name.begin());

    for (auto it : courses) {
      if (course_index->slot == it.slot) {
        for (auto jt : student_index->courses) {
          if (jt == it.name) {
            cout << "fail\n";
            return;
          }
        }
      }
    }

    if (student_index->courses.size() == student_index->max_courses) {
      cout << "fail\n";
      return;
    }
    // cout << course_index->students.size() << "size" << course_index->max_reg
    //  << "\n";
    if (course_index->students.size() == course_index->max_reg) {
      cout << "fail\n";
      return;
    }

    for (auto it : student_index->courses) {
      if (it == cou) {
        cout << "fail\n";
        return;
      }
    }

    for (auto it : course_index->students) {
      if (it == stu) {
        cout << "fail\n";
        return;
      }
    }

    student_index->courses.push_back(cou);
    course_index->students.push_back(stu);
    course_index->students.sort();
    student_index->courses.sort();

    cout << "success\n";
    return;
  }

  void drop(string stu, string cou) {
    pair<vector<string>::iterator, vector<string>::iterator> student_indices;
    student_indices =
        equal_range(students_name.begin(), students_name.end(), stu);
    if (student_indices.first == student_indices.second) {
      cout << "fail\n";
      return;
    }

    pair<vector<string>::iterator, vector<string>::iterator> course_indices;
    course_indices = equal_range(courses_name.begin(), courses_name.end(), cou);
    if (course_indices.first == course_indices.second) {
      cout << "fail\n";
      return;
    }

    vector<Course>::iterator course_index =
        courses.begin() + (course_indices.first - courses_name.begin());
    vector<Student>::iterator student_index =
        students.begin() + (student_indices.first - students_name.begin());

    // if (student_index->courses.size() == student_index->max_courses) {
    //   cout << "fail\n";
    //   return;
    // }
    // cout << course_index->students.size() << "size" << course_index->max_reg
    //      << "\n";
    // if (course_index->students.size() == course_index->max_reg) {
    //   cout << "fail\n";
    //   return;
    // }

    list<string>::iterator iter;
    // string findString = "Cinco";

    if ((iter = find(student_index->courses.begin(),
                     student_index->courses.end(), cou)) !=
        student_index->courses.end()) {
      student_index->courses.erase(iter);
      if ((iter = find(course_index->students.begin(),
                       course_index->students.end(), stu)) !=
          course_index->students.end()) {
        course_index->students.erase(iter);
        cout << "success\n";
        return;
      }
    }
    cout << "fail\n";
    return;
    // for (auto it : student_index->courses) {
    //   if (it == cou) {
    //     student_index->courses.erase(it);
    //     for (auto jt : course_index->students) {
    //       if (jt == stu) {
    //         course_index->students.erase(jt);
    //         cout << "success\n";
    //         return;
    //       }
    //     }
    //     break;
    //   }
    // }

    // cout << "fail\n";
    // return;
  }

  void print1(string stu) {
    pair<vector<string>::iterator, vector<string>::iterator> student_indices;
    student_indices =
        equal_range(students_name.begin(), students_name.end(), stu);

    vector<Student>::iterator student_index =
        students.begin() + (student_indices.first - students_name.begin());

    for (auto it : student_index->courses) {
      cout << it << " ";
    }
    cout << "\n";
    return;
  }

  void print2(string cou) {
    pair<vector<string>::iterator, vector<string>::iterator> course_indices;
    course_indices = equal_range(courses_name.begin(), courses_name.end(), cou);
    vector<Course>::iterator course_index =
        courses.begin() + (course_indices.first - courses_name.begin());

    for (auto it : course_index->students) {
      cout << it << " ";
    }
    cout << "\n";
    return;
  }

  void print3(string stu1, string stu2) {
    pair<vector<string>::iterator, vector<string>::iterator> student_indices_1;
    student_indices_1 =
        equal_range(students_name.begin(), students_name.end(), stu1);

    vector<Student>::iterator student_index_1 =
        students.begin() + (student_indices_1.first - students_name.begin());

    pair<vector<string>::iterator, vector<string>::iterator> student_indices_2;
    student_indices_2 =
        equal_range(students_name.begin(), students_name.end(), stu2);

    vector<Student>::iterator student_index_2 =
        students.begin() + (student_indices_2.first - students_name.begin());

    list<string> common_data;
    for (list<string>::iterator it = student_index_1->courses.begin(),
                                jt = student_index_2->courses.begin();
         it != student_index_1->courses.end() &&
         jt != student_index_2->courses.end();) {
      if (*it < *jt) {
        it++;
      } else if (*it > *jt) {
        jt++;
      } else {
        common_data.push_back(*it);
        it++;
        jt++;
      }
    }

    for (auto it : common_data) {
      cout << it << " ";
    }
    cout << "\n";
    return;
  }

  void print4(string cou1, string cou2) {
    pair<vector<string>::iterator, vector<string>::iterator> course_indices_1;
    course_indices_1 =
        equal_range(courses_name.begin(), courses_name.end(), cou1);

    vector<Course>::iterator course_index_1 =
        courses.begin() + (course_indices_1.first - courses_name.begin());

    pair<vector<string>::iterator, vector<string>::iterator> course_indices_2;
    course_indices_2 =
        equal_range(courses_name.begin(), courses_name.end(), cou2);

    vector<Course>::iterator course_index_2 =
        courses.begin() + (course_indices_2.first - courses_name.begin());

    list<string> common_data;
    for (list<string>::iterator it = course_index_1->students.begin(),
                                jt = course_index_2->students.begin();
         it != course_index_1->students.end() &&
         jt != course_index_2->students.end();) {
      if (*it < *jt) {
        it++;
      } else if (*it > *jt) {
        jt++;
      } else {
        common_data.push_back(*it);
        it++;
        jt++;
      }
    }

    for (auto it : common_data) {
      cout << it << " ";
    }
    cout << "\n";
    return;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int courses_count, students_count, max_courses, ops;
  cin >> courses_count >> students_count >> max_courses >> ops;
  if (max_courses == -1) {
    max_courses = courses_count;
  }
  Acad ac(courses_count, students_count, max_courses);

  string line, str1, str2;
  char ch1, ch2[6], ch3[9];
  int line_size;
  for (int i = 0; i < ops; i++) {
    cin >> ch1;
    if (ch1 == 'R') {
      cin >> str1 >> str2;
      // cout << str1 << " " << str2 << "\n";
      ac.reg(str1, str2);
    } else if (ch1 == 'D') {
      cin >> str1 >> str2;
      // cout << str1 << " " << str2 << "\n";
      ac.drop(str1, str2);
    } else if (ch1 == 'P') {
      getline(cin, line);
      line_size = line.size();
      if (line_size == 7) {
        str1.assign(line.begin() + 1, line.begin() + 7);
        ac.print2(str1);
      } else if (line_size == 10) {
        str1.assign(line.begin() + 1, line.begin() + 10);
        ac.print1(str1);
      } else if (line_size == 14) {
        str1.assign(line.begin() + 1, line.begin() + 7);
        str2.assign(line.begin() + 8, line.begin() + 14);
        ac.print4(str1, str2);
      } else if (line_size == 20) {
        str1.assign(line.begin() + 1, line.begin() + 10);
        str2.assign(line.begin() + 11, line.begin() + 20);
        ac.print3(str1, str2);
      }
      // cin >> str1;
      // cout << line.size() << "\n";
    }
  }
  return 0;
}
