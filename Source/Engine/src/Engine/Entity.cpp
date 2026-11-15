#include "Engine/Entity.h"
#include "Engine/TransformComponent.h"
#include "Engine/ComponentRegistry.h"

Entity::Entity()
{
	m_transform = &AddComponent<TransformComponent>();
}

Component* Entity::AddComponent(const std::string componentName)
{
	std::unique_ptr<Component> comp = ComponentRegistry::Get().Create(componentName);

	comp->SetOwner(this);

	Component* ptr = comp.get();

	m_components.Add(std::move(comp));

	return ptr;
}