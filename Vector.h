#ifndef _VECTOR_H_
#define _VECTOR_H_

template <class T>
class Vector
{
public:

	Vector();
	Vector(const Vector<T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

	T& operator[](int);
	T& operator[](int) const;

	void useSort();
	void print();

	void pushBack(const T&);
	void pop(int);
	void pop();
	int getSize() const { return capacity; }
	int getNumberOfElements() const { return size; }
	T* getContainer() const { return container; }

private:

	void mergeSort(T*, int);
	void mergeSortStep(T*, int, T*);
	void merge(T*, int, T*, int, T*);

	void reSize(int);
	void copyElements(const Vector<T>&);

	T* container;
	int size;
	int capacity;

};

#endif // !_VECTOR_H_
