#ifndef _PAIR_H_
#define _PAIR_H_

template <class T>
class Pair
{
private:

	T data;
	float counter;

	void copyElements(const Pair<T>& other)
	{
		data = other.data;
		counter = other.counter;
	}

public:

	Pair(): counter(0){}

	Pair(const T& data) : data(data){ counter = 0.0; ++counter; }

	Pair(const Pair<T>& other)
	{
		copyElements(other);
	}

	Pair<T>& operator=(const Pair<T>& other)
	{
		if (this != &other)
		{
			copyElements(other);
		}

		return *this;
	}

	~Pair(){}

	Pair<T> operator+(const Pair<T>& other)
	{
		Pair<T> result;
		result.counter	=  this->counter + other.counter;

		return result;
	}

	bool operator<(const Pair& other) const
	{
		if (counter < other.counter)
		{
			return true;
		}

		return false;
	}

	bool operator==(const Pair& other)const 
	{
		if (counter == other.counter)
		{
			return true;
		}

		return false;
	}

	T getData() const { return data; }
	float getCount() const { return counter; }
};

#endif // !_PAIR_H_
