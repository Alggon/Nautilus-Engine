#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include "Engine/Entity.h"


class TestComponent : public Component
{
	using Component::Component;
};

TEST_CASE("Entity - Transform", "[Entity]")
{
	Entity* e = new Entity();

	TransformComponent* p = e->GetComponent<TransformComponent>();

	REQUIRE(&e->Transform());
	REQUIRE(p == &e->Transform());
}

TEST_CASE("Entity - Add & Get", "[Entity]")
{
	Entity* e = new Entity();

	Component* p = &e->AddComponent<TestComponent>();
	Component* l = e->GetComponent<TestComponent>();

	REQUIRE(p == l);
	REQUIRE(e->Size() == 2); // With Transform
}

TEST_CASE("Entity - Remove", "[Entity]")
{
	Entity* e = new Entity();

	e->AddComponent<TestComponent>();

	bool success = e->RemoveComponent<TestComponent>();

	REQUIRE(success);
	REQUIRE(e->Size() == 1); // Keep Transform
}

TEST_CASE("Entity - Get wrong type", "[Entity]")
{
	Entity* e = new Entity();

	Component* p = e->GetComponent<TestComponent>();

	REQUIRE(p == nullptr);
}