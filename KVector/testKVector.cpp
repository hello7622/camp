#include "KVector.h"
#include "KVector.cpp"
#include <iostream>
using namespace std;

int main() {
    // KVector<int>(const std::initializer_list<int>&);
    KVector<int> vec{1, 2, 3, 4, 5};
    cout << "vec: ";
    // 
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\nvec.size() | operator[]\n";
    // 
    for (const auto& i : vec) {
        cout << i << " ";
    }
    cout << "\nbegin() | end()\n";
    // 
    for (int i = 6; i <= 11; i++) {
        vec.push(i);
    }
    for (const auto& i : vec) {
        cout << i << " ";
    }
    cout << "\npush(const T&, size_t)扩容\n";
    // 
    vec.pop();
    for (const auto& i : vec) {
        cout << i << " ";
    }
    cout << "\npop(size_t)";
    // KVector(const KVector&)
    KVector<int> vec2(vec);
    for (const auto& i : vec2) {
        cout << i << " ";
    }
    cout << "\nKVector(const KVector&)\n";
    // clear()
    vec.clear();
    cout << vec.size() << endl;
    // 
    vec2 = vec;
    for (size_t i = 0; i < vec2.size(); i++) {
        cout << i << " ";
    }
    cout << "\noperator=(const KVector&)\n";
    cout << vec2.index(3) << endl;
    cout << vec2.at(2) << endl;
    return 0;
}
