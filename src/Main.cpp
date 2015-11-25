#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <memory>

#include "GameLoop.h"

	//global for ease of use, not recommended tho
	SDL_Window* window = NULL;
	SDL_GLContext gContext;

	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	
//Initialise Opengl
bool initGL(){

	GLenum error = GL_NO_ERROR;
	//set Matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	error = glGetError();
	if(error != GL_NO_ERROR){
		std::cout << "ERROR" << std::endl;
		return false;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	error = glGetError();
	if(error != GL_NO_ERROR){
		std::cout << "ERROR" << std::endl;
		return false;
	}
	//set color to use when you clear the gl
	glClearColor(0.f, 0.f, 0.f, 1.f);
	return true;

	
}

//Initialise SDL
bool Init(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
			std::cout << "Could not Initialize SDL" << std::endl;
		}else{
			//set GL version
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
			//create window
			window = SDL_CreateWindow("SDL OPENGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if(window == NULL){
				std::cout << " WINDOW NOT CREATED!" << std::endl;
			}else{
				//create GL context
				gContext = SDL_GL_CreateContext(window);
				if(gContext == NULL){
					std::cout <<"Context not created" << std::endl;
				}else{
					//set Vsync
					if(SDL_GL_SetSwapInterval(1) < 0){
						std::cout << "VSync not Init" << std::endl;
					}
					if(!initGL()){
						std::cout << "GL not init" << std::endl;
						return false;
					}
				}
				return true;
			
			}
		}


}

//close programs
bool Quit(){
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Update(){
	
}

//render
void Render(){
	
}

int main(){

	auto  game_loop = std::make_shared<GameLoop>();
	
	
	bool running;
	//if program inits properly, set game to running
	Init();
	game_loop->StartLoop(window);
	
	Quit();
	
	return 0;
}
