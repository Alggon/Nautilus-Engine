#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "Engine/Component.h"

#define REGISTER_COMPONENT(TYPE) \
inline static const bool s_registered_##TYPE = ComponentRegistry::Get().Register<TYPE>(#TYPE);

class ComponentRegistry
{
public :
	ComponentRegistry(const ComponentRegistry& c) = delete;
	ComponentRegistry& operator=(const ComponentRegistry& other) = delete;

	const std::unique_ptr<Component> Create(const std::string& name);

	template<std::derived_from<Component> T>
	const bool Register(std::string name)
	{
		return Register(std::move(name), [] {return std::make_unique<T>(); });
	}

	static ComponentRegistry& Get();

	void Clear();

private :
	ComponentRegistry() = default;
	~ComponentRegistry() = default;

	const bool Register(std::string name, std::function<std::unique_ptr<Component>()> func);

	std::unordered_map < std::string, std::function<std::unique_ptr<Component>()>> m_factories;
};