# all:
#     g++ -I/usr/include/SDL -c GameGraphics.cpp -o GameGraphics.o
# 	g++ -I/usr/include/SDL -c GameState.cpp -o GameState.o
# 	g++ -I/usr/include/SDL -c main.cpp -o main.o
# 	g++  -o NombreEjecutable GameGraphics.o GameState.o main.o  -L/usr/lib/x86_64-linux-gnu -lSDL
algo: GameGraphics.o GameState.o main.o
	g++  -o main GameGraphics.o GameState.o main.o  -L/usr/lib/x86_64-linux-gnu -lSDL

main: main.cpp
	g++ -c main.cpp -o main.o

state: GameState.cpp GameState.h
	g++ -c GameState.cpp -o GameState.o

graphic: GameGraphics.cpp GameGraphics.h
	g++ -c GameGraphics.cpp -o GameGraphics.o

clean:
	rm *.o main