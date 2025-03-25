#ifndef __KVECTOR_H__
#define __KVECTOR_H__

#include <cstddef>
#include <initializer_list>

template <typename T>
class KVector 
{
public:
    typedef const T* Iterator; 

    KVector();
    KVector(const KVector& vec);
    KVector& operator=(const KVector& vec);
    KVector(KVector&& vec);
    KVector& operator=(KVector&& vec);
    virtual ~KVector();

    KVector(size_t size, const T& value = T());
    KVector(const std::initializer_list<T>& list);

    void push(const T& value, size_t index = -1);
    void pop(size_t index = -1);
    void clear();

    size_t size() const;
    size_t index(const T& value) const;
    bool empty() const;
    T& at(size_t index);
    T& operator[](size_t index);
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;

    Iterator begin() const;
    Iterator end() const;

protected:
    void resize(size_t newCapacity);
    void destroy();
private:
    T* m_pVec;
    size_t m_size;
    size_t m_capacity;
};

#endif // __KVECTOR_H__
