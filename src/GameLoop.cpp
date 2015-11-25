#include "GameLoop.h"



void GameLoop::StartLoop(SDL_Window* window){



bool running = true;


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

}

void GameLoop::Update(){

	//check if certain keys are pressed and edit camera position as needed
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
	//Move gl space
	glTranslatef(-gCameraX, -gCameraY, 0.f);
	glPushMatrix;

}

void GameLoop::Render(){

	
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
		
		glTranslatef(1.f, 1.f, 0.f);		

		glBegin(GL_QUADS);
		  glColor3f( 1.f, 1.f, 1.f);
		  glVertex2f( -0.5f, -0.5f );
                  glVertex2f( 0.5f, -0.5f );
		  glColor3f(0.f, 1.f, 0.f);
                  glVertex2f( 0.5f, 0.5f );
                  glVertex2f( -0.5f, 0.5f );
                glEnd();


		glTranslatef(1.f, -1.f, 0.f);		

		glBegin(GL_QUADS);
		  glColor3f( 1.f, 1.f, 1.f);
		  glVertex2f( -0.5f, -0.5f );
                  glVertex2f( 0.5f, -0.5f );
		  glColor3f(0.f, 1.f, 0.f);
                  glVertex2f( 0.5f, 0.5f );
                  glVertex2f( -0.5f, 0.5f );
                glEnd();
		
		glTranslatef(-1.f, -1.f, 0.f);	
		glBegin(GL_QUADS);
		  glColor3f( 0.f, 1.f, 1.f);
		  glVertex2f( -0.5f, -0.5f );
                  glVertex2f( 0.5f, -0.5f );
		  glColor3f(1.f, 1.f, 0.f);
                  glVertex2f( 0.5f, 0.5f );
                  glVertex2f( -0.5f, 0.5f );
                glEnd();
}
