#include <iostream>
#include <bitset>
using namespace std;
#define M 20

int main() {
    bitset<M> a(2), b(1);

    cout << (~a | b) << endl;
}
