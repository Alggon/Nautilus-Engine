#pragma once

class DynArray
{
public:
	DynArray() { m_data = new int[0]; };
	~DynArray() { delete[] m_data; };

	void Add(int v)
	{
		size_t currentSize = m_size;
		++m_size;

		int* newData = new int[m_size];

		if (m_data)
		{
			std::copy(m_data, m_data + currentSize, newData);
			delete[] m_data;
		}

		m_data = newData;
		m_data[m_size - 1] = v;
	};

	void RemoveAt(int index)
	{
		if (m_size == 0 || index < 0 || index >= m_size) return;

		if (m_size == 1)
		{
			delete[] m_data;
			m_data = nullptr;
			return;
		}

		size_t currentSize = m_size;
		--m_size;

		int* newData = new int[m_size];

		size_t newIndex = 0;
		for (size_t i = 0; i < currentSize; ++i)
		{
			if (i != index)
			{
				newData[newIndex] = m_data[i];
				++newIndex;
			}
		}

		delete[] m_data;

		m_data = newData;
	}

	int& operator[](size_t i) { return m_data[i]; };
	size_t Num() const { return m_size; };

private:
	size_t m_size = 0, m_capacity = 1024;
	int* m_data;
};