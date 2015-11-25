OBJS = src/*.cpp

OBJ_NAME = Run

all: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -lGL -lGLU -lglut --std=c++11 -o$(OBJ_NAME)
