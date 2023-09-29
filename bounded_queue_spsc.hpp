#pragma once

#include <atomic>
#include <optional>
#include "circular_queue.hpp"


template <typename T>
class bounded_queue_spsc
{
public:

	explicit bounded_queue_spsc(size_t cap = 5)
		: m_size(0)
		, m_queue(cap)
	{}

	bounded_queue_spsc(const bounded_queue_spsc&) = delete;

public:

	bool push(T val);
	std::optional<T> pop();

private:

	std::atomic<size_t>     m_size;

	circular_queue<T>		m_queue;
};


template<typename T>
bool bounded_queue_spsc<T>::push(T val)
{
	if (m_size.load(std::memory_order_relaxed) >= m_queue.capacity())
		return false;

	m_queue.push(val);
	m_size.fetch_add(1, std::memory_order_release);
	return true;
}


template<typename T>
std::optional<T> bounded_queue_spsc<T>::pop()
{
	if (m_size.load(std::memory_order_acquire) == 0)
	{
		return std::optional<T>(std::nullopt);
	}
	else
	{
		std::optional<T> res(m_queue.pop());
		m_size.fetch_sub(1, std::memory_order_relaxed);
		return res;
	}
}

