#include "Engine/Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Windows.h"

int main()
{
	EngineHello();

	HMODULE dll = LoadLibraryA("GameCode.dll");

	if (!dll) { std::cout << "GameCode.dll has not been found.\n"; return 1; }

	auto GameHello = (void(*)())GetProcAddress(dll, "GameHello");
	if (!GameHello) { std::cout << "GameHello has not been found.\n"; return 2; }

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Nautilus");

	while (window.isOpen())
	{
		GameHello();

		sf::Event e;
		
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		window.display();
	}

	FreeLibrary(dll);

	return 0;
}