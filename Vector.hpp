#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <cstring>
#include "Vector.h"

template <class T>
inline Vector<T>::Vector()
{
	container = nullptr;
	size = 0;
	capacity = 0;
}

template <class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	delete[] container;
	copyElements(other);
}

template <class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		delete[] container;
		copyElements(other);
	}

	return *this;
}

template <class T>
inline void Vector<T>::copyElements(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;

	container = new(std::nothrow) T[capacity];
	if (!container)
	{
		std::cout << "Can't allocate memory in copyElements in Vector!!\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		container[i] = other.container[i];
	}
}

template <class T>
inline void Vector<T>::pushBack(const T& other)
{
	if (capacity == 0)
	{
		reSize(1);
	}
	else if (capacity == size)
	{
		reSize(capacity * 2);
	}

	container[size] = other;
	++size;
}

template <class T>
inline void Vector<T>::reSize(int newSize)
{
	T* tmpContainer = new(std::nothrow) T[newSize];
	if (!tmpContainer)
	{
		std::cout << "Can't allocate memory in reSize in Vector\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		tmpContainer[i] = container[i];
	}

	delete[] container;
	container = tmpContainer;
	tmpContainer = nullptr;

	capacity = newSize;
}

template <class T>
inline void Vector<T>::pop(int index)
{
	if (capacity == 0)
	{
		std::cout << "Nothing to delete\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		if (index >= 0 && index <= size - 1)
		{
			container[i] = container[i + 1];
		}
	}

	--size;

	if (size == 0)
	{
		return;
	}
	else if (size < capacity / 4)
	{
		reSize(capacity / 2);
	}
}

template <class T>
inline void Vector<T>::pop()
{
	if (capacity == 0)
	{
		std::cout << "Nothing to delete\n";
		return;
	}

	--size;

	if (size == 0)
	{
		return;
	}
	else if (size < capacity / 4)
	{
		reSize(capacity / 2);
	}
}

template <class T>
inline T& Vector<T>::operator[](int index)
{
	if (index < 0 || index >= capacity)
	{
		std::cout << "Out of array bounds in Vector in []\n";
		return container[index];
	}

	return container[index];
}

template <class T>
inline T& Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= capacity)
	{
		std::cout << "Out of array bounds in Vector in []\n";
		return container[index];
	}

	return container[index];
}

template <class T>
inline Vector<T>::~Vector()
{
	delete[] container;
}

template <class T>
inline void Vector<T>::merge(T* left, int sizeLeft, T* right, int sizeRight, T* dest)
{
	int iL = 0, iR = 0, i = 0;

	while (iL < sizeLeft && iR < sizeRight)
	{
		if (left[iL] < right[iR])
		{
			dest[i] = left[iL];
			i++;
			iL++;
		}
		else
		{
			dest[i] = right[iR];
			i++;
			iR++;
		}
	}

	while (iL < sizeLeft)
	{
		dest[i] = left[iL];
		i++;
		iL++;
	}

	while (iR < sizeRight)
	{
		dest[i] = right[i];
		i++;
		iR++;
	}
}

template <class T>
inline void Vector<T>::mergeSortStep(T* arrPointer, int size, T* buffer)
{
	if (size <= 1)
	{
		return;
	}

	int middle = size / 2;

	mergeSortStep(arrPointer, middle, buffer);

	mergeSortStep(arrPointer + middle, size - middle, buffer + middle);

	merge(arrPointer, middle, arrPointer + middle, size - middle, buffer);

	for (int i = 0; i < size; ++i)
	{
		arrPointer[i] = buffer[i];
	}
}

template <class T>
inline void Vector<T>::mergeSort(T* arrPointer, int size)
{
	if (!arrPointer || size == 0)
	{
		return;
	}

	T* buffer = new(std::nothrow) T[size];

	mergeSortStep(arrPointer, size, buffer);

	delete[] buffer;
}

template <class T>
inline void Vector<T>::useSort()
{
	mergeSort(container, size);
}

template <class T>
inline void Vector<T>::print()
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
}

#endif //!_VECTOR_HPP_