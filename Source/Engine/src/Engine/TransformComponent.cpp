#include "Engine/TransformComponent.h"

void TransformComponent::Translate(const double& x, const double& y)
{
	m_position += Vec2(x, y);
}
void TransformComponent::Translate(const Vec2& vec)
{
	m_position += vec;
}

void TransformComponent::SetPosition(const double& x, const double& y)
{
	m_position = Vec2(x, y);
}

void TransformComponent::SetPosition(const Vec2& vec)
{
	m_position = vec;
}
