CC=g++
CFLAGS=-c -Wall
CLIBS=-lGLEW -lglfw -lGL
OBJECTS=shader.o


all: solution

solution: solution.cpp $(OBJECTS)
	$(CC) $(CLIBS) $(OBJECTS) solution.cpp -o solution

shader.o: shader.cpp shader.hpp
	$(CC) $(CFLAGS)  shader.cpp -o shader.o

clean:
	rm -rf *o solution
