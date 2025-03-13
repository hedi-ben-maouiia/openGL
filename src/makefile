CXX   := g++ 
LIB   := -lglfw -lGL 
FLAGS := -Wall -Wextra -ggdb
SRC   := main.cpp glad.c shaders.cpp

main: main.cpp
	${CXX} -o main ${SRC} ${LIB} ${FLAGS}

run:
	./main
clean:
	rm -rf main
