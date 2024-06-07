#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <vector>
using namespace std;

class Screen{
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	vector<SDL_Point> vec;
	public:
	Screen(int width, int height){
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 1, 1);
	}

	void pixel(float x, float y)
	{
		vec.emplace_back(x,y);
	}

	void show()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderDrawPoints(renderer, vec.data(), vec.size());
		SDL_RenderPresent(renderer);
	}

	void input()
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(0);
			}
		}
	}

	void line(int x1, int y1, int x2, int y2)
	{
		SDL_SetRenderDrawColor(renderer,255,0,0,255);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
	void clear()
	{
		vec.clear();
	}
};
