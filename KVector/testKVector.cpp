#include "KVector.h"
#include "KVector.cpp"
#include <iostream>
using namespace std; 

int main() {
    // KVector<int>(const std::initializer_list<int>&);
    KVector<int> vec{1, 2, 3, 4, 5};
    cout << "\n<--vec.size() | operator[]-->\n"
    	 << "vec: ";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    
    cout << "\n<--begin() | end()-->\n";
    for (const auto& i : vec) {
        cout << i << " ";
    }
    
    cout << "\n<--push(const T&, size_t)扩容-->\n";
    for (int i = 6; i <= 11; i++) {
        vec.push(i);
    }
    for (const auto& i : vec) {
        cout << i << " ";
    }
    
    cout << "\n<--pop(size_t)-->\n";
    vec.pop();
    for (const auto& i : vec) {
        cout << i << " ";
    }
    
    cout << "\n<--KVector(const KVector&)-->\n";
    KVector<int> vec2(vec);
    for (const auto& i : vec2) {
        cout << i << " ";
    }
    
    vec.clear();
    cout << "\n<--clear-->\n" << vec.size()
    	 << "\n<--empty-->\n" << vec.empty();
    
    cout << "\n<--operator=(const KVector&)-->\n";
    vec2 = vec;
    for (const auto& val : vec2) {
        cout << val << " ";
    }
    
    cout << "\n<--index not found-->\n" << vec2.index(3);
    
    try {
    	cout << "\n<--at-->\n"
			 << vec2.at(2) << endl;
	} catch (std::out_of_range& e) {
		cout << e.what();
	}
	
	cout << "\n<--KVector(size_t, const T&) | operator=(KVector&&)-->\n";
	vec2 = KVector<int>(10, 5);
	for (const auto& val : vec2) {
		cout << val << " ";
	}
	
	cout << "\n<--KVector(KVector&&)-->\n";
	KVector<int> vec3(KVector<int>{1, 2, 3, 4, 5});
	for (const auto& val : vec3) {
		cout << val << " ";
	}
	
	cout << "\n<--index found-->\n" << vec3.index(4)
		 << "\n<--at-->\n" << vec3.at(4)
	 	 << "\n<--not empty-->\n" << vec3.empty();
    return 0;
}
