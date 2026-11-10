#pragma once
#include <utility>
#include <memory>
#include <iostream>

template<typename T>
class DynArray
{
public:
	DynArray() { m_data = m_allocator.allocate(m_capacity); };

	~DynArray()
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			// Destroy every element
			std::destroy_at(&m_data[i]);
		}

		// Complete deallocation
		m_allocator.deallocate(m_data, m_capacity);
	};

	void Add(const T& v)
	{
		if (m_size == m_capacity)
		{
			std::cout << "Increase capacity" << std::endl;

			// Increase array capacity
			size_t previousCapacity = m_capacity;
			m_capacity *= 2;
			T* newData = m_allocator.allocate(m_capacity);

			// Copy previous data in the new array
			for (size_t i = 0; i < m_size; ++i)
			{
				// Create element into the new array
				std::construct_at(&newData[i], std::move(m_data[i]));
				// Delete element in previous array
				std::destroy_at(&m_data[i]);
			}

			m_allocator.deallocate(m_data, previousCapacity);

			m_data = newData;
		}

		// Construct new element
		std::construct_at(&m_data[m_size], v);

		// Update array size
		++m_size;
	};

	void RemoveAt(int index)
	{
		// Security
		if (m_size == 0 || index < 0 || index >= m_size) return;

		// Shrink
		for (size_t i = index; i < m_size - 1; ++i)
		{
			// Move to the left
			m_data[i] = std::move(m_data[i + 1]);
		}

		// Delete element
		std::destroy_at(&m_data[m_size - 1]);
		// Update array size
		--m_size;
	}

	T& operator[](const size_t i) { return m_data[i]; };
	size_t Num() const { return m_size; };
	size_t Capacity() const { return m_capacity; };

private:
	size_t m_size = 0;
	size_t m_capacity = 1;

	T* m_data;

	std::allocator<T> m_allocator;
};