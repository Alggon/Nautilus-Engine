#pragma once
#include <iostream>

class Entity;

class Component
{
public :
	Component() = default;
	~Component() = default;

	void SetOwner(Entity* owner) { m_owner = owner; };
	Entity* GetOwner() { return m_owner; };

	virtual void Update() {};

protected :
	Entity* m_owner = nullptr;
};