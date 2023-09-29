#pragma once

#include <mutex>
#include <condition_variable>
#include "circular_queue.hpp"


template <typename T>
class bounded_queue_mt
{
public:

	bounded_queue_mt(size_t cap = 5)
	    : m_mutex()
		, m_cond_var()
		, m_queue(cap)
	{}

	bounded_queue_mt(const bounded_queue_mt&) = delete;

public:

	bool push(T val);
	T pop();

private:

	mutable std::mutex		m_mutex;
	std::condition_variable m_cond_var;

	circular_queue<T>		m_queue;

};


template<typename T>
bool bounded_queue_mt<T>::push(T val)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	if (m_queue.push(val))
	{
		m_cond_var.notify_one();
		return true;
	}

	return false;
}


template<typename T>
T bounded_queue_mt<T>::pop()
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_cond_var.wait(lk, [this] {return !m_queue.empty(); });
	
	return m_queue.pop();
}

