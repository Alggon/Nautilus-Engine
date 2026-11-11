#pragma once
#include <utility>
#include <memory>
#include <bit>
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

	/// <summary>
	/// Add element to the array (back).
	/// </summary>
	/// <param name="v"> : Element to add</param>
	void Add(const T& v)
	{
		if (m_size == m_capacity)
		{
			// Expand capacity
			Reserve();
		}

		// Construct new element
		std::construct_at(&m_data[m_size], v);

		// Update array size
		++m_size;
	};
	/// <summary>
	/// Add element to the array (front).
	/// </summary>
	/// <param name="v"> : Element to add</param>
	void Add_Front(const T& v)
	{
		// Insert new element at index 0
		InsertAt(0, v);
	}
	/// <summary>
	/// Insert element at wanted index.
	/// </summary>
	/// <param name="index"> : Wanted index</param>
	/// <param name="v"> : Element to add</param>
	/// <returns>Success</returns>
	bool InsertAt(const size_t index, const T& v)
	{
		if (index > m_size) return false;

		if (m_size == m_capacity)
		{
			// Expand capacity
			Reserve();
		}

		for (size_t i = m_size; i > index; --i)
		{
			// Move to the right
			m_data[i] = std::move(m_data[i - 1]);
		}

		m_data[index] = v;
		++m_size;

		return true;
	}
	/// <summary>
	/// Remove every occurence of an element in the array.
	/// </summary>
	/// <param name="v"> : Element to remove</param>
	/// <returns>Success</returns>
	bool Remove(const T& v)
	{
		// Security
		if (m_size == 0) return false;
		// index to remove
		DynArray<int> indexes;

		for (size_t i = 0; i < m_size; ++i)
		{
			// Find element to remove
			if (m_data[i] == v)
			{
				// Stock indexes
				indexes.Add_Front(i);
			}
		}

		if (indexes.Empty()) return false;

		// for each element iteration
		for (const int i : indexes)
		{
			// Remove at found index
			RemoveAt(i);
		}

		return true;
	}
	/// <summary>
	/// Remove element at wanted index.
	/// </summary>
	/// <param name="index"> : Wanted index</param>
	/// <returns>Success</returns>
	bool RemoveAt(const size_t index)
	{
		// Security
		if (m_size == 0 || index < 0 || index >= m_size) return false;

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

		return true;
	}
	/// <summary>
	/// Shrinks array to the nearest superior bit.
	/// </summary>
	void Shrink_To_Fit()
	{
		size_t previousCapacity = m_capacity;
		// Shrink array capacity to bit ceil
		m_capacity = std::bit_ceil(m_size);

		T* newData = m_allocator.allocate(m_capacity);

		// Copy previous data in the new array
		for (size_t i = 0; i < m_size; ++i)
		{
			// Create element into the new array
			std::construct_at(&newData[i], std::move(m_data[i]));
			// Delete element in previous array
			std::destroy_at(&m_data[i]);
		}

		// Free previous block memory
		m_allocator.deallocate(m_data, previousCapacity);
		// Attribute new block
		m_data = newData;
	}

	/// <summary>
	/// Returns number of elements.
	/// </summary>
	size_t Size() const { return m_size; };
	/// <summary>
	/// Returns number of reserved blocks.
	/// </summary>
	size_t Capacity() const { return m_capacity; };
	/// <summary>
	/// Returns if the array is empty or not.
	/// </summary>
	bool Empty() const { Size() == 0; };

	T& operator[](const size_t i) { return m_data[i]; };
	T* begin() { return &m_data[0]; };
	T* end() { return &m_data[m_size]; };

private:
	size_t m_size = 0;
	size_t m_capacity = 64;

	T* m_data;

	std::allocator<T> m_allocator;

	/// <summary>
	/// Reserve more space for the array.
	/// </summary>
	void Reserve()
	{
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

		// Free previous block memory
		m_allocator.deallocate(m_data, previousCapacity);
		// Attribute new block
		m_data = newData;
	}
};