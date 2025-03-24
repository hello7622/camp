#include "KVector.h"

template <typename T>
KVector<T>::KVector()
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
    resize(10);
}

template <typename T>
KVector<T>::KVector(const KVector& vec)
    : m_data(nullptr)
    , m_size(vec.m_size)
    , m_capacity(0)
{
    resize(vec.m_capacity);
    std::copy(vec.m_data, vec.m_data + m_size, m_data);
}

template <typename T>
KVector<T> &KVector<T>::operator=(const KVector &vec)
{
    if (this == &vec) {
        return *this;
    }
    if (m_capacity < vec.m_size) {
        destroy();
        resize(vec.m_size << 1);
    }
    m_size = vec.m_size;
    std::copy(vec.m_data, vec.m_data + m_size, m_data);
    return *this;
}

template <typename T>
KVector<T>::~KVector()
{
    destroy();
}

template <typename T>
void KVector<T>::push(const T &value, size_t index)
{
    if (m_size == m_capacity) {
        resize(m_capacity << 1);
    }
    // index非负，故不设index == -1时的处理
    if (index >= m_size) {
        m_data[m_size++] = value;
    } else {
        for (size_t i = m_size; i > index; --i) {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = value;
        ++m_size;
    }
}

template <typename T>
void KVector<T>::pop(size_t index)
{
    if (m_size == 0) {
        return;
    }
    if (index >= m_size) {
        index = m_size - 1;
    }
    for (size_t i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
}

template <typename T>
void KVector<T>::clear()
{
    m_size = 0;
}

template <typename T>
size_t KVector<T>::size() const
{
    return m_size;
}

template <typename T>
size_t KVector<T>::index(const T &value) const
{
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool KVector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
T &KVector<T>::at(size_t index)
{
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_data[index];
}

template <typename T>
T &KVector<T>::operator[](size_t index)
{
    return at(index);
}

template <typename T>
const T &KVector<T>::at(size_t index) const
{
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_data[index];
}

template <typename T>
const T &KVector<T>::operator[](size_t index) const
{
    return at(index);
}

template <typename T>
void KVector<T>::resize(size_t newCapacity)
{
    if (newCapacity == m_capacity) {
        return;
    }
    T* newData = new T[newCapacity];
    if (m_data) {
        std::copy(m_data, m_data + m_size, newData);
        delete[] m_data;
    }
    m_data = newData;
    m_capacity = newCapacity;
}

template <typename T>
void KVector<T>::destroy()
{
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}