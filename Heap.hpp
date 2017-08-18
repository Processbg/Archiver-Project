#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#include <iostream>
#include "Heap.h"

template <class T>
inline Heap<T>::Heap(const Heap<T>& other)
{
	container = other.container;
}

template <class T>
inline Heap<T>& Heap<T>::operator=(const Heap<T>& other)
{
	if (this != &other)
	{
		container = other.container;
	}

	return *this;
}

template <class T>
inline void Heap<T>::swap(T& first, T& second)
{
	T tmp;
	tmp = first;
	first = second;
	second = tmp;
}

template <class T>
inline void Heap<T>::reHeapUp(int indexInVector)
{
	if (indexInVector > 0)
	{ 
		int parentIndex = (indexInVector - 1)/ 2;

		if (container[parentIndex] > container[indexInVector])
		{
			swap(container[parentIndex], container[indexInVector]);
			reHeapUp(parentIndex);
		}
	}
}

template <class T>
inline void Heap<T>::insert(const T& key)
{	
	container.pushBack(key);
	int end = container.getNumberOfElements() - 1;
	heapSize++;
	reHeapUp(end);
}

template <class T>
inline void Heap<T>::reHeapDown(int indexInVector)
{	
	int bottom = container.getNumberOfElements() - 1;

	if (indexInVector < bottom)
	{
		int rightChildIndex = (indexInVector * 2) + 2;
		int leftChildIndex = (indexInVector * 2) + 1;
		int minChildIndex = 0;

		if (leftChildIndex < bottom && container[indexInVector] > container[leftChildIndex])
		{
			minChildIndex = leftChildIndex;

			if (rightChildIndex < bottom && container[leftChildIndex] > container[rightChildIndex])
			{
				minChildIndex = rightChildIndex;
			}

		}
		else if (rightChildIndex < bottom && container[indexInVector] > container[rightChildIndex])
		{
			minChildIndex = rightChildIndex;
		}

		if (minChildIndex != 0)
		{
			swap(container[indexInVector], container[minChildIndex]);
			reHeapDown(minChildIndex);
		}
	}
}

template <class T>
inline void Heap<T>::remove()
{
	if (heapSize == 0)
	{
		return;
	}

	int end = container.getNumberOfElements() - 1;
	
	swap(container[0], container[end]);

	container.pop();
	heapSize--;
	reHeapDown(0);
}

template <class T>
inline void Heap<T>::print()
{
	int size = container.getNumberOfElements();
	for (int i = 0; i < size; ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
}

template <class T>
inline T Heap<T>::getHightestPriority()
{
	T result;
	result = container[0];
	remove();

	return result;
}

template <class T>
inline bool Heap<T>::isEmpty() const
{
	return heapSize == 0;
}


#endif // !_HEAP_HPP_
