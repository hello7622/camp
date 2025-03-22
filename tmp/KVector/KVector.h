#ifndef __KVECTOR_H__
#define __KVECTOR_H__

#include <initializer_list>

template<typename T>
class KVector {
	public:
		KVector();
		~KVector();

		KVector(const KVector<T>& _other);
		KVector<T>& operator=(const KVector<T>& _list);

		KVector(const std::initializer_list<T>& _list);
		KVector(int _num, const T& _val = T());

		class Iterator {
			public:
			friend class KVector;
			Iterator(T * _ptr, T * _begin, T * _end);
			Iterator(const Iterator& _other);
			T& operator*();
			Iterator& operator++();
			Iterator& operator--();
			Iterator operator+(int _off);
			Iterator operator-(int _off);
			bool operator==(const Iterator& _other);
			bool operator!=(const Iterator& _other);
			private:
			T *cur, *begin, *end;
		};
		
		int size() const;
		int length() const;
		T& front() const;
		T& back() const;
		Iterator begin() const;
		Iterator end() const;
		Iterator find(const T& _val);
		
		KVector<T>& operator<<(const T& _val);
		void append(const T& _val);
		void append(const T& _val, const Iterator& _pos);
		void remove(const T& _val);
		void remove(const Iterator& _pos);
		void extend(const KVector<T>& _list);
		void clear();
		
		T& operator[](int num);
		T& operator[](int num) const;
		bool operator==(const KVector<T>& _list);
		KVector<T> operator+(const KVector<T>& _list) const;
		KVector<T>& operator+=(const KVector<T>& _list);
	protected:
		T* ReAlloc(int _containerLength);
	private:
		const int minContainerLength;
		int containerLength, len;
		T * list;
};

#endif // __KVECTOR_H__
