OBJS = src/*.cpp

OBJ_NAME = Run

all: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -lGL -lGLU -lglut -o$(OBJ_NAME)
