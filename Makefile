all: GameGraphics.o GameSounds.o GameState.o main.o
	g++  -o main GameGraphics.o GameSounds.o GameState.o main.o  -L/usr/lib/x86_64-linux-gnu -lSDL

main: main.cpp
	g++ -c main.cpp -o main.o

state: GameState.cpp GameState.h
	g++ -c GameState.cpp -o GameState.o

graphic: GameGraphics.cpp GameGraphics.h
	g++ -c GameGraphics.cpp -o GameGraphics.o

sound: GameSounds.cpp GameSounds.h
	g++ -c GameSounds.cpp -o GameSounds.o

clean:
	rm *.o main