c=g++ -std=c++17 -Wall -Wextra -c -g
normal=g++ -std=c++17 -Wall -Wextra -g
sfml=-lsfml-graphics -lsfml-window -lsfml-system

all: main

main: parse.o math.o calculate.o interpreter.o simulation.o input.o particle.o graphics.o structures.o main.o
	$(normal) $(sfml) parse.o math.o calculate.o interpreter.o particle.o simulation.o input.o graphics.o structures.o main.o -o main

main.o: parse.hpp structures.hpp calculate.hpp interpreter.hpp particle.hpp simulation.hpp input.hpp graphics.hpp main.cpp
	$(c) main.cpp -o main.o

graphics.o: particle.o particle.hpp graphics.cpp
	$(c) graphics.cpp -o graphics.o

simulation.o: particle.o structures.o particle.hpp structures.hpp simulation.cpp
	$(c) simulation.cpp -o simulation.o

input.o: particle.o interpreter.o particle.hpp interpreter.hpp input.cpp
	$(c) input.cpp -o input.o

structures.o: structures.cpp structures.hpp
	$(c) structures.cpp -o structures.o

calculate.o: structures.o calculate.cpp
	$(c) calculate.cpp -o calculate.o

interpreter.o: parse.o parse.hpp particle.hpp interpreter.cpp
	$(c) interpreter.cpp -o interpreter.o

math.o: parse.o math.hpp math.cpp
	$(c) math.cpp -o math.o

parse.o: parse.cpp
	$(c) parse.cpp -o parse.o

particle.o: structures.o math.o particle.cpp
	$(c) particle.cpp -o particle.o

clean:
	if [ -n "*.o" ]; then rm *.o; fi
	if [ -f "main" ]; then rm main; fi

#written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved
