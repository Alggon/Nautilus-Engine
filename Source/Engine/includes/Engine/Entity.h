#pragma once
#include <concepts>
#include "Core/DynArray.h"
#include "Engine/TransformComponent.h"

class Entity
{
public:
	Entity();
	~Entity() = default;

	/// <summary>
	/// Add a new component of type T. T should inherit from Component, otherwise function will not compile.
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	/// <typeparam name="T"></typeparam>
	/// <param name="...args"></param>
	/// <returns> : Newly created component.</returns>
	template<std::derived_from<Component> T, typename ...Args>
	T& AddComponent(Args... args)
	{
		// Create unique_ptr of type T with args
		std::unique_ptr<T> comp = std::make_unique<T>(std::forward<Args>(args)...);
		// Setup component owner
		comp->SetOwner(this);
		// Get raw ptr
		T* rawPtr = comp.get();
		// Add comp to component array
		m_components.Add(std::move(comp));
		// Return raw ptr
		return *rawPtr;
	}
	/// <summary>
	/// Remove first component of type T. T should inherit from Component, otherwise function will not compile.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns> : Success</returns>
	template<std::derived_from<Component> T>
	const bool RemoveComponent()
	{
		// Iterate over comp array
		for (size_t i = 0; i < m_components.Size(); ++i)
		{
			// cast to T type
			if (dynamic_cast<T*>(m_components[i].get()))
			{
				// if cast is valid, remove first comp of type T
				m_components.RemoveAt(i);
				// Success
				return true;
			}
		}

		// Fail
		return false;
	}
	/// <summary>
	/// Remove all components of type T. T should inherit from Component, otherwise function will not compile.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::derived_from<Component> T>
	void RemoveComponents()
	{
		// Iterate over comp array
		for (size_t i = 0; i < m_components.Size(); ++i)
		{
			// cast to T type
			if (dynamic_cast<T*>(m_components[i].get()))
			{
				// if cast is valid, remove this comp of type T...
				m_components.RemoveAt(i);
				// ...And continue
				--i;
			}
		}
	}
	/// <summary>
	/// Get first component of type T. T should inherit from Component, otherwise function will not compile.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns> : First component of type T</returns>
	template<std::derived_from<Component> T>
	T* GetComponent()
	{
		// Iterate over comp array
		for (size_t i = 0; i < m_components.Size(); ++i)
		{
			// Cast to T type
			T* castedComp = dynamic_cast<T*>(m_components[i].get());

			if (castedComp != nullptr)
			{
				// if cast is valid, return raw ptr
				return castedComp;
			}
		}

		// No component of T type
		return nullptr;
	}
	/// <summary>
	/// Get first component of type T. T should inherit from Component, otherwise function will not compile.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns> : First component of type T</returns>
	template<std::derived_from<Component> T>
	const T* GetComponent() const
	{
		// Iterate over comp array
		for (size_t i = 0; i < m_components.Size(); ++i)
		{
			// Cast to T type
			T* castedComp = dynamic_cast<T*>(m_components[i].get());

			if (castedComp != nullptr)
			{
				// if cast is valid, return raw ptr
				return castedComp;
			}
		}

		// No component of T type
		return nullptr;
	}
	/// <summary>
	/// Returns transform component, every entity has its own transform component.
	/// </summary>
	TransformComponent& Transform() { return *m_transform; };
	/// <summary>
	/// Returns size of the component array.
	/// </summary>
	const size_t Size() { return m_components.Size(); };

private:
	DynArray<std::unique_ptr<Component>> m_components;

	TransformComponent* m_transform = nullptr;
};