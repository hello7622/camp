#include "KString.h"
#include "KString.cpp"

#include <iostream>

int main() {
    KString str1("Hello, ");
    KString str2("World!");

    KString str3 = str1 + str2;
    std::cout << "str3: " << str3 << std::endl;

    str3[6] = 'W';
    std::cout << "str3 after modifying: " << str3 << std::endl;

    return 0;
}