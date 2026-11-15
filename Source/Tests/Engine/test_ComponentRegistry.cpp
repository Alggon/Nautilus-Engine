#include "Engine/EngineMinimal.h"
#include <catch2/catch_test_macros.hpp>

class ComponentTest : public Component
{
	using Component::Component;
};

TEST_CASE("ComponentRegistry - Registering Component", "[ComponentRegistry]")
{
	ComponentRegistry::Get().Clear();

	const bool registered = ComponentRegistry::Get().Register<ComponentTest>("ComponentTest");

	REQUIRE(registered);
}

TEST_CASE("ComponentRegistry - Duplicate register", "[ComponentRegistry]")
{
	ComponentRegistry::Get().Clear();
	ComponentRegistry::Get().Register<ComponentTest>("ComponentTest");

	const bool registered = ComponentRegistry::Get().Register<ComponentTest>("ComponentTest");

	REQUIRE(!registered);
}

TEST_CASE("ComponentRegistry - Create Component", "[ComponentRegistry]")
{
	ComponentRegistry::Get().Clear();
	ComponentRegistry::Get().Register<ComponentTest>("ComponentTest");

	std::unique_ptr<Component> comp = ComponentRegistry::Get().Create("ComponentTest");

	Component* ptr = comp.get();

	REQUIRE(ptr != nullptr);
}