#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
	//global for ease of use, not recommended tho
	SDL_Window* window = NULL;
	SDL_GLContext gContext;

	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	GLfloat gCameraX = 0.f, gCameraY = 0.f;
	const Uint8 *state;
	
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
	if(state[SDL_SCANCODE_UP]){
		gCameraY -= 0.05f;
	}
	if(state[SDL_SCANCODE_DOWN]){
		gCameraY += 0.05f;
	}
	if(state[SDL_SCANCODE_LEFT]){
		gCameraX -= 0.05f;
	}
	if(state[SDL_SCANCODE_RIGHT]){
		gCameraX += 0.05f;
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.f);
	glPushMatrix;
}

//render
void Render(){
	//clear GL context
	glClear(GL_COLOR_BUFFER_BIT);

		//Draw polygon, change colours	
		glBegin(GL_QUADS);
		  glColor3f( 0.f, 1.f, 1.f);
		  glVertex2f( -0.5f, -0.5f );
                  glVertex2f( 0.5f, -0.5f );
		  glColor3f(1.f, 1.f, 0.f);
                  glVertex2f( 0.5f, 0.5f );
                  glVertex2f( -0.5f, 0.5f );
                glEnd();

}

int main(){

	bool running;
	//if program inits properly, set game to running
	running = Init();
	SDL_Event e;	
	//used to calculate FPS
	unsigned int FPSupdate = SDL_GetTicks();
	unsigned int currentTime;	
	int FPS = 0;
	state = SDL_GetKeyboardState(NULL);	
	//constantly loop while running
	while(running){
		
		Update();

		
		Render();
		//update window 
		SDL_GL_SwapWindow(window);

		//if program is asked to close, leave loop
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				running = false;
			}
		}
		//used for FPS counter
		currentTime = SDL_GetTicks();
		if((currentTime - FPSupdate) > 1000){
			std::cout << FPS << std::endl;
			FPSupdate = SDL_GetTicks();					
			FPS = 0;
		}
		
		FPS++;
		

	}
	
	Quit();
	
	return 0;
}
