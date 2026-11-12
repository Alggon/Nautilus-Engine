#include "Engine/Engine.h"
#include <SFML/Graphics.hpp>
#include "Engine/Entity.h"

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
			Entity* entity = new Entity();
			
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			
			delete entity;
		}

		window.clear();

		window.display();
	}

	EngineShutdown();

	return 0;
}