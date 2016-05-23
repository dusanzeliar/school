#Makefile
#Riesenie ICP-PROJEKT,  6.5.2014
#Autor: Dusan Zeliar,xzelia00, FIT
#       Filip Mutnansky, xmutna00, FIT

ZIP = zip -r

CPPFLAGS=-std=c++11

ZIP_FILE = xzelia00-xmutna00.zip
PACKED_FILES = src examples doc doxyconf Makefile README.txt
DOXY_DIR = doc
DOXY_FILE = doxyconf


all: labyrinth2015
#.PHONY: clean

pack: clean
	$(ZIP) $(ZIP_FILE) $(PACKED_FILES)

run: labyrinth2015
	./labyrinth2015

#game
labyrinth2015: src/game.o src/field.o src/stone.o src/cards.o src/board.o src/player.o src/input.o src/output.o src/labyrinth.o src/save.o src/load.o
	g++ $(CPPFLAGS) src/cards.o src/game.o src/stone.o src/field.o src/board.o src/player.o src/input.o src/output.o src/labyrinth.o src/save.o src/load.o -o $@

input.o: src/input.cpp src/input.h
	g++ $(CPPFLAGS) -c src/input.cpp -o $@

save.o: src/save.cpp src/save.h
	g++ $(CPPFLAGS) -c src/save.cpp -o $@

load.o: src/load.cpp src/load.h
	g++ $(CPPFLAGS) -c src/load.cpp -o $@

output.o: src/output.cpp src/output.h src/board.h src/stone.h
	g++ $(CPPFLAGS) -c src/output.cpp -o $@

cards.o: src/cards.cpp src/cards.h
	g++ $(CPPFLAGS) -c src/cards.cpp -o $@

stone.o: src/stone.cpp src/stone.h
	g++ $(CPPFLAGS) -c src/stone.cpp -o $@

field.o: src/stone.cpp src/stone.h src/field.cpp src/field.h
	g++ $(CPPFLAGS) -c src/field.cpp -o $@

board.o: src/board.cpp src/board.h src/stone.cpp src/stone.h 
	g++ $(CPPFLAGS) -c src/board.cpp -o $@

player.o: src/player.cpp src/player.h src/stone.h src/field.h 
	g++ $(CPPFLAGS) -c src/player.cpp -o $@

game.o: src/game.cpp src/game.h src/cards.h src/player.h src/board.h src/input.h src/output.h
	g++ $(CPPFLAGS) -c src/game.cpp -o $@

labyrinth.o: src/labyrinth.cpp src/game.h
	g++ $(CPPFLAGS) -c src/labyrinth.cpp -o $@

doxygen:
	doxygen doxyconf

cleansavedgames:
	rm -f *_board *_players *_cards

clean:
	rm -f src/*.o 
	rm -f labyrinth2015 
	rm -rf doc/html 
	rm -rf doc/latex
