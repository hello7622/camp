#include "KVector.h"

template<typename T>
KVector<T>::KVector()
	: minContainerLength(10)
	, containerLength(minContainerLength)
	, len(0)
	, list(new T[containerLength]) {

}

template<typename T>
KVector<T>::KVector(const KVector<T>& _other)
	: minContainerLength(10)
	, containerLength(minContainerLength)
	, len(0)
	, list(new T[containerLength]) {
	for (const T& val : _other) {
		append(val);
	}
}

template<typename T>
KVector<T>::KVector(const std::initializer_list<T>& _list)
	: minContainerLength(10)
	, containerLength(minContainerLength)
	, len(0)
	, list(new T[containerLength]) {
	for (const T& val : _list) {
		append(val);
	}
}

template<typename T>
KVector<T>::KVector(int _num, const T& _val)
	: minContainerLength(10)
	, containerLength(minContainerLength)
	, len(0)
	, list(nullptr) {
	if (2 * _num > minContainerLength) {
		containerLength = 2 * _num;
	}
	list = new T[containerLength];
	for (int i = 0; i < _num; i++) {
		list[i] = _val;
	}
	len = _num;
}

template<typename T>
KVector<T>::~KVector() {
	if (list) {
		delete[] list;
		list = nullptr;
	}
	containerLength = len = 0;
}

template<typename T>
void KVector<T>::clear() {
	len = 0;
}

template<typename T>
KVector<T>& KVector<T>::operator=(const KVector<T>& _list) {
	if (containerLength < _list.length()) {
		containerLength  = _list.length() * 2;
		T * ptr = ReAlloc(containerLength);
		if (list) {
			delete[] list;
		}
		list = ptr;
	}
	len = _list.length();
	for (int i = 0; i < len; i++) {
		list[i] = _list[i];
	}
	return *this;
}

template<typename T>
bool KVector<T>::operator==(const KVector<T>& _list) {
	if (len != _list.length()) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (list[i] != _list[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
T& KVector<T>::operator[](int num) {
	if (num < 0 || num >= len) {
		return list[len];
	}
	return list[num];
}

template<typename T>
T& KVector<T>::operator[](int num) const {
	if (num < 0 || num >= len) {
		return list[len];
	}
	return list[num];
}

template<typename T>
int KVector<T>::size() const {
	return len;
}

template<typename T>
int KVector<T>::length() const {
	return len;
}

template<typename T>
void KVector<T>::append(const T& _val) {
	if (len + 1 >= containerLength) {
		containerLength = len * 2;
		T * ptr = ReAlloc(containerLength);
		if (list) {
			delete[] list;
		}
		list = ptr;
	}
	list[len] = _val;
	++len;
}

template<typename T>
void KVector<T>::remove(const T& _val) {
	int pos = 0;
	for (; pos < len; pos++) {
		if (list[pos] == _val) {
			break;
		}
	}
	for (int i = pos; i < len; i++) {
		list[i] = list[i + 1];
	}
	--len;
	if (len * 4 < containerLength) {
		if (len * 2 > minContainerLength) {
			containerLength = len * 2;
		} else {
			containerLength = minContainerLength;
		}
		delete[] (list + containerLength);
	}
}

template<typename T>
T& KVector<T>::front() const {
	return operator[](0);
}

template<typename T>
T& KVector<T>::back() const {
	return operator[](len - 1);
}

template<typename T>
KVector<T>& KVector<T>::operator<<(const T& _val) {
	append(_val);
	return *this;
}

template<typename T>
KVector<T>::Iterator::Iterator(T * _ptr, T * _begin, T * _end)
	: cur(_ptr)
	, begin(_begin)
	, end(_end) {

}

template<typename T>
KVector<T>::Iterator::Iterator(const Iterator& _other)
	: cur(_other.cur)
	, begin(_other.begin)
	, end(_other.end) {

}

template<typename T>
T& KVector<T>::Iterator::operator*() {
	return *cur;
}

template<typename T>
typename KVector<T>::Iterator& KVector<T>::Iterator::operator++() {
	if (cur < end) {
		++cur;
	}
	return *this;
}

template<typename T>
typename KVector<T>::Iterator& KVector<T>::Iterator::operator--() {
	if (cur > begin) {
		--cur;
	}
	return *this;
}

template<typename T>
typename KVector<T>::Iterator KVector<T>::Iterator::operator+(int _off) {
	if (cur + _off >= end) {
		return Iterator(end, begin, end);
	}
	return Iterator(cur + _off, begin, end);
}

template<typename T>
typename KVector<T>::Iterator KVector<T>::Iterator::operator-(int _off) {
	if (cur - _off <= begin) {
		return Iterator(begin, begin, end);
	}
	return Iterator(cur - _off, begin, end);
}

template<typename T>
bool KVector<T>::Iterator::operator==(const Iterator& _other) {
	return cur == _other.cur;
}

template<typename T>
bool KVector<T>::Iterator::operator!=(const Iterator& _other) {
	return cur != _other.cur;
}

template<typename T>
typename KVector<T>::Iterator KVector<T>::begin() const {
	return Iterator(list, list, list + len);
}

template<typename T>
typename KVector<T>::Iterator KVector<T>::end() const {
	return Iterator(list + len, list, list + len);
}

template<typename T>
void KVector<T>::append(const T& _val, const Iterator& _pos) {
	if (_pos.begin != list) {
		return ;
	}
	if (len + 1 >= containerLength) {
		containerLength = len * 2;
		T * ptr = ReAlloc(containerLength);
		if (list) {
			delete[] list;
		}
		list = ptr;		
	}
	T * ptr = list + len;
	for (; ptr > _pos.cur; ptr--) {
		*ptr = *(ptr - 1);
	}
	*ptr = _val;
	++len;
}

template<typename T>
void KVector<T>::remove(const Iterator& _pos) {
	if (_pos.begin != list || _pos.cur == list + len) {
		return ;
	}
	T * ptr = _pos.cur;
	for (; ptr < list + len; ptr++) {
		*ptr = *(ptr + 1);
	}
	--len;
	if (len * 4 < containerLength) {
		if (len * 2 > minContainerLength) {
			containerLength = len * 2;
		} else {
			containerLength = minContainerLength;
		}
		delete[] (list + containerLength);
	}
}

template<typename T>
void KVector<T>::extend(const KVector<T>& _list) {
	if (len + _list.length() >= containerLength) {
		containerLength = (len + _list.length()) * 2;
		T * ptr = ReAlloc(containerLength);
		if (list) {
			delete[] list;
		}
		list = ptr;		
	}
	for (int i = len; i < len + _list.length(); i++) {
		list[i] = _list[i - len];
	}	
	len += _list.length();
}

template<typename T>
KVector<T> KVector<T>::operator+(const KVector<T>& _list) const {
	KVector<T> ans(*this);
	ans.extend(_list);
	return ans;
}

template<typename T>
KVector<T>& KVector<T>::operator+=(const KVector<T>& _list) {
	extend(_list);
	return *this;
}

template<typename T>
typename KVector<T>::Iterator KVector<T>::find(const T& _val) {
	for (int i = 0; i < len; i++) {
		if (list[i] == _val) {
			return Iterator(list + i, list, list + len);
		}
	}
	return Iterator(list + len, list, list + len);
}

template<typename T>
T* KVector<T>::ReAlloc(int _containerLength) {
	T * ptr = new T[_containerLength];
	for (int i = 0; i < len; i++) {
		ptr[i] = list[i];
	}
	return ptr;
}
