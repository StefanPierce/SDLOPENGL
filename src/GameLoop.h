#include<iostream>
#include<memory>
#include<SDL2/SDL.h>
#include <GL/glu.h>

class GameLoop{
public:
	void StartLoop(SDL_Window* window);

	


private:
	
	void Update();
	void Render();
	GLfloat gCameraX = 0.f, gCameraY = 0.f;
	const Uint8 *state;
	
};
