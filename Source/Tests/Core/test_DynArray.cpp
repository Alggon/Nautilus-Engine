#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include "Core/DynArray.h"

class TestDummy
{
public:
	TestDummy() = default;
	~TestDummy() = default;
};

TEMPLATE_TEST_CASE("DynArray - Init", "[DynArray]", int, float, std::string, TestDummy*)
{
	DynArray<TestType> arr;

	REQUIRE(arr.Empty());
	REQUIRE(arr.Capacity() > 0);
}

TEMPLATE_TEST_CASE("DynArray - Add", "[DynArray]", int, float, std::string, TestDummy*)
{
	DynArray<TestType> arr;

	arr.Add(TestType{});
	REQUIRE(arr.Size() == 1);
}

TEMPLATE_TEST_CASE("DynArray - RemoveAt", "[DynArray]", int, float, std::string, TestDummy*)
{
	DynArray<TestType> arr;

	arr.Add(TestType{});
	arr.RemoveAt(0);
	REQUIRE(arr.Size() == 0);
}

TEMPLATE_TEST_CASE("DynArray - Remove", "[DynArray]", int, float, std::string, TestDummy*)
{
	DynArray<TestType> arr;

	TestType a = TestType{};

	arr.Add(a);
	arr.Add(a);
	
	arr.Remove(a);

	REQUIRE(arr.Empty());
}

TEMPLATE_TEST_CASE("DynArray - For Each", "[DynArray]", int, float, std::string, TestDummy*)
{
	DynArray<TestType> arr;

	int count = 0;

	arr.Add(TestType{});
	arr.Add(TestType{});
	arr.Add(TestType{});

	for (const TestType t : arr)
	{
		++count;
	}

	REQUIRE(count == arr.Size());
}

TEST_CASE("DynArray - Move simple types", "[DynArray]")
{
	DynArray<int> arr;
	arr.Add(10);
	arr.Add(20);
	arr.Add(30);

	arr.RemoveAt(1);

	REQUIRE(arr.Size() == 2);
	REQUIRE(arr[0] == 10);
	REQUIRE(arr[1] == 30);
}

TEST_CASE("DynArray - Move ptr", "[DynArray]")
{
	DynArray<TestDummy*> arr;

	TestDummy* a = new TestDummy();
	arr.Add(new TestDummy());
	arr.Add(a);

	arr.RemoveAt(0);

	REQUIRE(a == arr[0]);
}

TEST_CASE("DynArray - Back & Front", "[DynArray]")
{
	DynArray<int> arr;

	arr.Add(0);
	arr.Add(0);

	arr.Add_Front(1);
	arr.Add(2);

	REQUIRE(arr[0] == 1);
	REQUIRE(arr[3] == 2);
}