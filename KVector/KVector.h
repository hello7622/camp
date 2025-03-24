#ifndef __KVECTOR_H__
#define __KVECTOR_H__

template <typename T>
class KVector 
{
public:
    KVector(KVector&&) = delete;
    KVector& operator=(KVector&&) = delete;
    
    KVector();
    KVector(const KVector& vec);
    KVector& operator=(const KVector& vec);
    virtual ~KVector();

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
protected:
    void resize(size_t newCapacity);
    void destroy();
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif // __KVECTOR_H__
