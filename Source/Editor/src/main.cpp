#include <SDL3/SDL.h>

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
	}
	int width = 800;
	int height = 600;

	SDL_Window* win = SDL_CreateWindow("SDL3 Test", width, height, 0);

	if (win == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", win);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	bool running = true;

	while (running)
	{
		SDL_Event event{ 0 };

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
			{
				running = false;
				break;
			}
			}
		}
	}

	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}