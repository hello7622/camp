#ifndef __KSTRING_H__
#define __KSTRING_H__

#include <cstddef>
#include <cstring>
#include <ostream>

class KString {
    public:
        KString(const char * str = nullptr, size_t len = -1);
        KString(const KString & other, size_t len = -1);
        ~KString();
        KString& operator=(const KString& other);
        size_t size() const;
        class Iterator {
            public:
                Iterator(char * _ptr);
                char& operator*();
                Iterator& operator++();
                Iterator operator++(int);
                bool operator==(const Iterator& other);
                bool operator!=(const Iterator& other);
            private:
                char * _ptr;
        };
        Iterator begin();
        Iterator end();
        void push(char c, size_t pos = -1);
        void pop(size_t pos = -1);
        char& operator[](size_t pos);
        const char& operator[](size_t pos) const;
        KString operator+(const KString& other) const;
        KString& operator+=(const KString& other);
        KString& operator+=(const char * str);
        KString& operator+=(char c);
        KString slice(size_t begin, size_t end) const;
        KString operator()(size_t begin, size_t end) const;
        KString reverse() const;
        KString operator*(int num) const;
        KString& operator*=(int num);
        friend std::ostream& operator<<(std::ostream& os, const KString& str);
    protected:
        inline void reallocate(size_t new_capacity);
    private:
        char * ptr;
        size_t length, capacity;
};

#endif // __KSTRING_H__