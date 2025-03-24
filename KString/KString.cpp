#include "KString.h"

KString::KString(const char * str, size_t len) {
	if (str == nullptr) {
		length = 0;
		capacity = 10;
		ptr = new char[capacity] {0};
	} else {
		size_t x = strlen(str);
		length = (len > x) ? x : len;
		capacity = (length << 1);
		ptr = new char[capacity];
		strncpy(ptr, str, length);
	}
}

KString::KString(const KString &other, size_t len) {
	length = (len > other.length) ? other.length : len;
	capacity = other.capacity;
	ptr = new char[capacity];
	strncpy(ptr, other.ptr, length);
}

KString::~KString() {
	if (ptr != nullptr) {
		delete[] ptr;
	}
}

KString& KString::operator=(const KString& other) {
	if (this == &other) {
		return *this;
	}
	if (capacity < other.length) {
		delete[] ptr;
		capacity = other.capacity;
		ptr = new char[capacity];
	}
	length = other.length;
	strcpy(ptr, other.ptr);
	return *this;
}

size_t KString::size() const {
	return length;
}

KString::Iterator KString::begin() {
	return Iterator(ptr);
}

KString::Iterator KString::end() {
	return Iterator(ptr + length);
}

void KString::push(char c, size_t pos) {
	if (length + 1 >= capacity) {
		reallocate(capacity << 1);
	}
	if (pos >= length) {
		pos = length;
	}
	for (size_t i = length; i > pos; --i) {
		ptr[i] = ptr[i - 1];
	}
	ptr[pos] = c;
	++length;
}

void KString::pop(size_t pos) {
	if (pos >= length) {
		pos = length - 1;
	}
	for (size_t i = pos; i < length - 1; ++i) {
		ptr[i] = ptr[i + 1];
	}
	ptr[length - 1] = 0;
	--length;
}

char& KString::operator[](size_t pos) {
	return ptr[pos];
}

const char& KString::operator[](size_t pos) const {
	return ptr[pos];
}

KString KString::operator+(const KString &other) const {
	KString tmp(*this, length + other.length);
	for (size_t i = 0; i < other.length; ++i) {
		tmp.ptr[length + i] = other.ptr[i];
	}
	tmp.length += other.length;
	return tmp;
}

KString& KString::operator+=(const KString &other) {
	if (length + other.length >= capacity) {
		reallocate((length + other.length) << 1);
	}
	for (size_t i = 0; i < other.length; ++i) {
		ptr[length + i] = other.ptr[i];
	}
	length += other.length;
	return *this;
}

KString& KString::operator+=(const char *str) {
	size_t x = strlen(str);
	if (length + x >= capacity) {
		reallocate((length + x) << 1);
	}
	strcpy(ptr + length, str);
	length += x;
	return *this;
}

KString& KString::operator+=(char c) {
	push(c);
	return *this;
}

KString KString::slice(size_t begin, size_t end) const {
	return KString(ptr + begin, (end > length) ? length : (end - begin));
}

KString KString::operator()(size_t begin, size_t end) const {
	return slice(begin, end);
}

KString KString::reverse() const {
	KString tmp(*this);
	char c;
	for (size_t i = 0; i < (length >> 1); ++i) {
		c = tmp[i];
		tmp[i] = tmp[length - i - 1];
		tmp[length - i - 1] = c;
	}
	return tmp;
}

KString KString::operator*(int num) const {
	KString tmp;
	for (int i = 0; i < num; ++i) {
		tmp += *this;
	}
	return tmp;
}

KString& KString::operator*=(int num) {
	KString tmp(*this);
	for (int i = 1; i < num; ++i) {
		*this += tmp;
	}
	return *this;
}

inline void KString::reallocate(size_t new_capacity) {
	capacity = new_capacity;
	char *tmp = new char[capacity];
	strcpy(tmp, ptr);
	delete[] ptr;
	ptr = tmp;
}

KString::Iterator::Iterator(char *_ptr) : _ptr(_ptr) {}

char& KString::Iterator::operator*() {
	return *_ptr;
}
KString::Iterator& KString::Iterator::operator++() {
	++_ptr;
	return *this;
}
KString::Iterator KString::Iterator::operator++(int) {
	Iterator tmp = *this;
	++_ptr;
	return tmp;
}
bool KString::Iterator::operator==(const Iterator& other) {
	return _ptr == other._ptr;
}
bool KString::Iterator::operator!=(const Iterator& other) {
	return _ptr != other._ptr;
}

std::ostream& operator<<(std::ostream& os, const KString& str) {
//    for (size_t i = 0; i < str.size(); ++i) {
//        os << str[i];
//    }
	os << str.ptr;
	return os;
}
