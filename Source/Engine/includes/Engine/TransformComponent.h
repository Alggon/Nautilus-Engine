#pragma once
#include "Component.h"
#include "Core/Vec2.h"

class TransformComponent : public Component
{
	using Component::Component;

public:
	TransformComponent(const Vec2& vec) : m_position(vec) {};
	TransformComponent(const double& v) { m_position = Vec2(v); };
	TransformComponent(const double& x, const double& y) { m_position = Vec2(x, y); };

	void Translate(const double& x, const double& y);
	void Translate(const Vec2& vec);

	void SetPosition(const double& x, const double& y);
	void SetPosition(const Vec2& vec);

	Vec2 GetPosition() const { return m_position; };
	Vec2 GetScale() const { return m_scale; };
	float GetRotation() const { return m_rotation; };

private:
	Vec2 m_position = Vec2(0, 0);
	Vec2 m_scale = Vec2(1, 1);
	float m_rotation = 0.f;
};