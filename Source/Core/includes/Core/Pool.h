#pragma once
#include <cstddef>
#include <memory>
#include <new>
#include <utility>
#include <vector>

template<typename T, size_t ChunkSize = 4>
class Pool {
	struct Slot {
		alignas(T) std::byte data[sizeof(T)];
		bool alive = false;
	};

public:
	Pool() = default;
	Pool(const Pool&) = delete;
	Pool& operator=(const Pool&) = delete;
	~Pool() { ForEach([](T& v) {v.~T(); }); m_Count = 0; };

	/// <summary>
	/// Add a new element to the pool, create a new chunk if no slot available.
	/// </summary>
	/// <param name="Args"></param>
	/// <returns>Pointer to the new object.</returns>
	template<typename... Args>
	T* Create(Args&&... args) 
	{	
		// If no free slot
		if (m_Free.empty()) {AddChunk();} 
		// Getting free slot
		Slot* s = m_Free.back();
		m_Free.pop_back();
		// Create object at slot memory adress
		T* obj = new (s->data) T(std::forward<Args>(args)...);
		// State update
		s->alive = true;
		++m_Count;

		return obj;
	}

	/// <summary>
	/// Destroy pointed object and free the assigned slot.
	/// </summary>
	/// <param name="obj"></param>
	void Destroy(T* obj)
	{
		// Convert obj into data
		Slot* s = reinterpret_cast<Slot*>(obj);
		// Destroy obj
		obj->~T();
		// State update
		s->alive = false;
		m_Free.push_back(s);
		--m_Count;
	}

	template<typename F>
	void ForEach(F&& f)
	{
		for (auto& chunk : m_Chunks)
			for (size_t i = 0; i < ChunkSize; ++i)
			{
				if (chunk[i].alive)
				{
					// Convert data into obj
					T* obj = reinterpret_cast<T*>(chunk[i].data);
					// Apply func on obj
					f(*obj);
				}
		}
	}

	/// <summary>
	/// Return the count of objects in this pool.
	/// </summary>
	size_t Count() const { return m_Count; };
	/// <summary>
	/// Return the count of chunks in this pool.
	/// </summary>
	size_t ChunksCount() const { return m_Chunks.size(); };

private:

	/// <summary>
	/// Create a new chunk and add its free slots to the list.
	/// </summary>
	void AddChunk()
	{
		m_Chunks.push_back(std::make_unique<Slot[]>(ChunkSize));

		Slot* c = m_Chunks.back().get();

		for (size_t i = ChunkSize; i-- > 0;)
		{
			m_Free.push_back(&c[i]);
		}
	}

	std::vector<std::unique_ptr<Slot[]>> m_Chunks;
	std::vector<Slot*> m_Free;
	size_t m_Count = 0;
};