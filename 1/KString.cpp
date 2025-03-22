#include "KString.h"

KString::KString(const char * str)
    : m_size(strlen(str)) {
    m_capacity = m_size << 1;
    if (m_capacity < 10) {
        m_capacity = 10;
    }
    m_data = new char[m_capacity];
    strncpy(m_data, str, m_capacity);
}


KString::~KString() {
    _destroy();
}

KString::KString(const KString &str) {
    _copy(str);
}

KString::KString(KString &&str) {
    _move(std::move(str));
}

KString &KString::operator=(const KString &str) {
    if (this != &str) {
        _copy(str);
    }
    return *this;
}

KString &KString::operator=(KString &&str) {
    if (this != &str) {
        _move(std::move(str));
    }
    return *this;
}

size_t KString::size() const {
    return m_size;
}

const char *KString::c_str() const
{
    return m_data;
}

KString KString::operator+(const KString &str) const {
    KString result(*this);
    result.m_size = m_size + str.m_size;
    result.m_capacity = result.m_size << 1;
    result._resize(result.m_capacity);
    strncpy(result.m_data + m_size, str.m_data, str.m_size);
    result.m_data[result.m_size] = '\0';
    return result;
}

KString &KString::operator+=(const KString &str)
{
    size_t size = m_size;
    m_size = m_size + str.m_size;
    m_capacity = m_size << 1;
    _resize(m_capacity);
    strncpy(m_data + size, str.m_data, str.m_size);
    m_data[m_size] = '\0';
    return *this;
}

char &KString::operator[](size_t index)
{
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_data[index];
}

const char &KString::operator[](size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_data[index];
}

bool KString::operator==(const KString &str) const {
    if (m_size!= str.m_size) {
        return false;
    }
    return memcmp(m_data, str.m_data, m_size) == 0;
}

void KString::_resize(size_t newSize) {
    if (newSize <= m_capacity) {
        return;
    }
    char * newData = new char[newSize];
    strncpy(newData, m_data, m_size);
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
    m_data = newData;
    m_capacity = newSize;
    m_size = m_size <= newSize? m_size : newSize;
}

void KString::_copy(const KString &str) {
    _resize(str.m_size);
    strncpy(m_data, str.m_data, m_size);
}

void KString::_move(KString &&str) {
    _resize(str.m_size);
    strncpy(m_data, str.m_data, m_size);
    str._destroy();
}

void KString::_destroy() {
    m_size = 0;
    m_capacity = 0;
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
}

std::istream &operator>>(std::istream &is, KString &str) {
    char buffer[1024];
    is.getline(buffer, sizeof(buffer));
    str = KString(buffer);
    return is;
}

std::ostream &operator<<(std::ostream &os, const KString &str) {
    os << str.m_data;
    return os;
}
