/// Can create function only for the game module here ///
//extern "C" __declspec(dllexport) void Func() {}

/// And then, can load dll and find functions with this code ///
/*
{
	// Needs this includes
	#include "Windows.h"
	#include <iostream>

	// Load dll
	HMODULE dll = LoadLibraryA("GameCode.dll");
	if (!dll) { std::cout << "GameCode.dll has not been found.\n"; return 1; }
	// Find function
	auto Func = (void(*)())GetProcAddress(dll, "Func");
	if (!Func) { std::cout << "Func has not been found.\n"; return 2; }
	// Use function
	Func();
	// Free dll
	FreeLibrary(dll);
}
*/