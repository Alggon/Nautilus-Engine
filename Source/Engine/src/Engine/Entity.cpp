#include "Engine/Entity.h"

Entity::Entity()
{
	m_transform = &AddComponent<TransformComponent>();
}