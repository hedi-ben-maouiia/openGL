CC=g++
FLAGS=-Wall -pedantic -g3  
LIBS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRC=main.cpp glad.c shaders.cpp textures.cpp oglib.cpp
BUILD=build


build: $(SRC) 
	$(CC) $(SRC) $(FLAGS) $(LIBS) -o $(BUILD)/opengl
run:
	./$(BUILD)/opengl
clean:
	rm -rf $(BUILD)/*

