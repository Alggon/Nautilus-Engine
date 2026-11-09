#include "Engine/Engine.h"
#include <iostream>

extern "C" __declspec(dllexport) void GameHello()
{
	std::cout << "Hello Game!\n";
}