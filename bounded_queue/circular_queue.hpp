#ifndef CIRCULAR_QUEUE
#define CIRCULAR_QUEUE

#include <stdexcept>
#include "my_aligned_storage.hpp"


template <typename T>
class circular_queue
{
public:

	circular_queue(size_t cap)
		: m_capacity(cap)
		, m_storage(cap + 1)
		, m_front(0)
		, m_rear(0)
	{}

	circular_queue(const circular_queue&) = delete;

	~circular_queue()
	{
		// destruct remaining objects
		for (size_t i = size(); i > 0; i--)
			pop();
	}

public:

	bool push(T val);
	T pop();

public:

	size_t capacity() const
	{
		return m_capacity;
	}

	size_t size() const
	{
		return m_front <= m_rear ? m_rear - m_front : capacity() + 1 - (m_front - m_rear);
	}

	bool full() const
	{
		return size() == capacity();
		//return m_front == inc(m_rear);
	}

	bool empty() const
	{
		return !size();
		//return m_front == m_rear;
	}

private:

	size_t                     m_capacity;
	my::aligned_storage<T>     m_storage;

	size_t                     m_front;
	size_t                     m_rear;

private:

	size_t inc(size_t x) const
	{
		return  (x + 1) % (capacity() + 1);
	}

	T* get_storage(size_t index) const
	{
		return (T*)m_storage[index];
	}
};


template <typename T>
bool circular_queue<T>::push(T val)
{
	if (full())
		return false;

	new (m_storage[m_rear]) T(val);
	m_rear = inc(m_rear);
	return true;
}


template <typename T>
T circular_queue<T>::pop()
{
	if (empty())
		throw std::runtime_error("Underflow!!!");

	T value = *get_storage(m_front);
	get_storage(m_front)->~T();
	m_front = inc(m_front);
	return value;
}

#endif CIRCULAR_QUEUE