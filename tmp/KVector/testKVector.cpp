#include "KVector.h"
#include "KVector.cpp"

#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& outo, const KVector<T>& list) {
	for (const T& elem : list) {
		outo << elem;
	}
	return outo;
}

KVector<int> range(int begin, int end, int step = 1) {
	KVector<int> ans;
	for (; begin < end; begin += step) {
		ans.append(begin);
	}
	return ans;
}

#include <string>
using namespace std;
typedef string TestType;
// int, char, string, KVector 测试成功 
int main() {
	KVector<KVector<int>> l(5, KVector<int>(5, 5));
	for (const auto& row: l) {
		for (const int& elem: row) {
			cout << elem;
		}
		cout << endl;
	}
	KVector<int> l1{1, 2, 3}, l2(3, 4);
	cout << (l1 + l2);
	return 0;
}
