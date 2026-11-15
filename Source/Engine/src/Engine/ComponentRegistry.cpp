#include "Engine/ComponentRegistry.h"

const std::unique_ptr<Component> ComponentRegistry::Create(const std::string& name)
{
	auto it = m_factories.find(name);
	if (it == m_factories.end())
	{
		return nullptr;
	}

	return it->second();
}

const bool ComponentRegistry::Register(std::string name, std::function<std::unique_ptr<Component>()> func)
{
	const bool inserted = m_factories.try_emplace(std::move(name), std::move(func)).second;

	if (!inserted)
	{
		// TODO : Error on insertion
	}

	return inserted;
}

ComponentRegistry& ComponentRegistry::Get()
{
	static ComponentRegistry instance;
	return instance;
}

void ComponentRegistry::Clear()
{
	m_factories.clear();
}
