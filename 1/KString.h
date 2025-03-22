#ifndef __KSTRING_H__
#define __KSTRING_H__

#include <cstddef>
#include <cstring>
#include <iostream>

class KString {
    public:
        KString(const char * str = nullptr);
        virtual ~KString();
        KString(const KString& str);
        KString(KString&& str);
        KString& operator=(const KString& str);
        KString& operator=(KString&& str);
        size_t size() const;
        const char* c_str() const;
        KString operator+(const KString& str) const;
        KString& operator+=(const KString& str);
        char& operator[](size_t index);
        const char& operator[](size_t index) const;
        bool operator==(const KString& str) const;
        friend std::istream& operator>>(std::istream& is, KString& str);
        friend std::ostream& operator<<(std::ostream& os, const KString& str);
    protected:
        void _resize(size_t newSize);
        void _copy(const KString& str);
        void _move(KString&& str);
        void _destroy();
    private:
        size_t m_size;
        size_t m_capacity;
        char* m_data;
};

#endif