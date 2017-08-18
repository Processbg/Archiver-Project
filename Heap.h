#ifndef _HEAP_H_
#define _HEAP_H_

#include "Vector.hpp"

template <class T>
class Heap
{
public:

	Heap(): heapSize(0){}
	Heap(const Heap<T>&);
	Heap<T>& operator=(const Heap<T>&);
	~Heap(){}

	bool isEmpty() const;
	void insert(const T&);
	void remove();
	void print();
	int getSize(){ return heapSize; }
	T getHightestPriority();

private:

	void reHeapUp(int);
	void reHeapDown(int);
	void swap(T&, T&);

	Vector<T> container;
	int heapSize;

};



#endif // !_HEAP_H_
