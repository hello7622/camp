#include "KString.h"
#include "KString.cpp"
#include <iostream>

using namespace std;
int main() {
    KString s("Hello, World!");
    for (const auto& c : s) {
        std::cout << c;
    } 
    s += '?';
    s += "?";
    std::cout << endl << s.reverse().slice(1, 4) << " " << s << endl;
	s *= -1;
	cout << s << endl;
	s = s * 0;
	s += "v2gr4r";
	cout << s;
    return 0;
}
