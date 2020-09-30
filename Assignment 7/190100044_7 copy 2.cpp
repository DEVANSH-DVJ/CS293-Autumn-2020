#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string.h>
#include <vector>
using namespace std;

bool string_less_than(char ch1[], char ch2[]) { return (strcmp(ch1, ch2) < 0); }

class Course {
public:
  char *name;
  int slot;
  int max_reg;
  list<char *> students;

  Course(char ch[6], int max, int slot_number) {
    name = new char[6];
    strcpy(name, ch);
    max_reg = max;
    slot = slot_number;
  }

  bool operator<(const Course &d) { return (strcmp(name, d.name) < 0); }

  // ~Course() { delete name; }
};

class Student {
public:
  char *name;
  int max_courses;
  list<char *> courses;

  Student(char ch[9], int max) {
    name = new char[9];
    name = ch;
    max_courses = max;
  }

  bool operator<(const Student &d) { return (strcmp(name, d.name) < 0); }

  // ~Student() { delete name; }
};

class Acad {
public:
  int courses_count, students_count, max_courses;
  vector<Course> courses;
  vector<Student> students;
  vector<char *> courses_name;
  vector<char *> students_name;

  Acad(int courses_count_, int students_count_, int max_courses_) {
    courses_count = courses_count_;
    students_count = students_count_;
    max_courses = max_courses_;

    char ch1[6];
    int c;
    int max;
    for (int i = 0; i < courses_count; i++) {
      cin >> ch1 >> c >> max;
      courses.push_back(Course(ch1, c, max));
    }

    for (int i = 0; i < courses_count; i++) {
      cout << courses[i].name <<";;;;;;;\n";
    }

    char ch2[9];
    for (int i = 0; i < students_count; i++) {
      cin >> ch2;
      cout << ch2 << "//\n";
      Student a(ch2, max_courses);
      students.push_back(a);
      cout << a.name << ";;\n";
    }

    sort(courses.begin(), courses.end());
    for (int i = 0; i < courses_count; i++) {
      courses_name.push_back(courses[i].name);
    }
    sort(students.begin(), students.end());
    for (int i = 0; i < students_count; i++) {
      students_name.push_back(students[i].name);
    }
    for (auto it: students_name) {
      cout << it <<".\n";
    }
  }

  void reg(char stu[], char cou[]) {
    pair<vector<char *>::iterator, vector<char *>::iterator> student_indices;
    student_indices = equal_range(students_name.begin(), students_name.end(),
                                  stu, string_less_than);
    cout << "hi" << endl;
    if (student_indices.first == student_indices.second) {
      cout << "Failure\n";
      return;
    }

    cout << "hi" << endl;
    pair<vector<char *>::iterator, vector<char *>::iterator> course_indices;
    course_indices = equal_range(courses_name.begin(), courses_name.end(), cou,
                                 string_less_than);
    if (course_indices.first == course_indices.second) {
      cout << "Failure\n";
      return;
    }

    cout << "hi" << endl;
    vector<Course>::iterator course_index =
        courses.begin() + (course_indices.first - courses_name.begin());
    vector<Student>::iterator student_index =
        students.begin() + (student_indices.first - students_name.begin());

    if (student_index->courses.size() == student_index->max_courses) {
      cout << "Failure\n";
      return;
    }
    if (course_index->students.size() == course_index->max_reg) {
      cout << "Failure\n";
      return;
    }

    for (auto it : student_index->courses) {
      if (strcmp(it, cou)) {
        cout << "Failure\n";
        return;
      }
    }

    for (auto it : course_index->students) {
      if (strcmp(it, stu)) {
        cout << "Failure\n";
        return;
      }
    }

    student_index->courses.push_back(cou);
    course_index->students.push_back(stu);
    cout << "Success\n";
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

  // string line;
  // char ch1, ch2[6], ch3[9];
  // for (int i = 0; i < ops; i++) {
  //   // cin >> ch1;
  //   getline(cin, line);
  //   if (line[0] == 'R') {
  //     // cin >> ch1;
  //     for (int i = 0; i < 9; i++) {
  //       ch3[i] = line[i + 2];
  //     }
  //     for (int i = 0; i < 6; i++) {
  //       ch2[i] = line[i + 11];
  //     }
  //     // cin >> ch3 >> ch2;
  //     cout << ch2 << " " << ch3 << "\n";
  //     // ac.reg(ch3, ch2);
  //   }
  // }

  string line, str1, st2;
  char ch1, ch2[6], ch3[9];
  for (int i = 0; i < ops; i++) {
    cin >> ch1;
    if (ch1 == 'R') {
      cin >> ch3 >> ch1 >> ch2;
      // getline(cin, str1, ' ');
      // cout << str1 << "\n";
      // cout << ch3 << " " << ch2 << "\n";
      ac.reg(ch3, ch2);
    }
  }
  return 0;
}
