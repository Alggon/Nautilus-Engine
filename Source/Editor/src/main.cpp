#include "Engine/Engine.h"
#include <SFML/Graphics.hpp>

int main()
{
	EngineStart();
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Nautilus");

	while (window.isOpen())
	{
		EngineTick();

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

	EngineShutdown();

	return 0;
}