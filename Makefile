PACKAGES = clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8
LIBS = `pkg-config --libs $(PACKAGES)`
OPTIONS =  -I/usr/local/include/ClanLib-0.8 -Iincludes -Wall -g
LINKER_OPTIONS =  #-u malloc #-lefence

all: includes/*.h bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o skins/aqua.zip
	@echo "On assemble le fichier final"
	g++ bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o $(LIBS) -Wall $(LINKER_OPTIONS) -o openalchemist 

bin/main.o : includes/*.h src/main.cpp
	g++ -c -o bin/main.o src/main.cpp $(OPTIONS) 

bin/game.o: includes/*.h src/game.cpp
	g++ -c -o bin/game.o src/game.cpp $(OPTIONS) 

bin/key_events.o : includes/*.h src/key_events.cpp
	g++ -c -o bin/key_events.o src/key_events.cpp  $(OPTIONS) 

bin/detect_to_destroy.o : includes/*.h src/detect_to_destroy.cpp
	g++ -c -o bin/detect_to_destroy.o src/detect_to_destroy.cpp $(OPTIONS)

bin/detect_to_fall.o : includes/*.h src/detect_to_fall.cpp
	g++ -c -o bin/detect_to_fall.o src/detect_to_fall.cpp $(OPTIONS)

bin/drawing.o : includes/*.h src/drawing.cpp
	g++ -c -o bin/drawing.o src/drawing.cpp $(OPTIONS)

bin/hightscores.o: includes/*.h src/hightscores.cpp
	g++ -c -o bin/hightscores.o src/hightscores.cpp $(OPTIONS)

bin/pause.o : includes/*.h src/pause.cpp
	g++ -c -o bin/pause.o src/pause.cpp $(OPTIONS)

skins:
skins/aqua.zip : skins/aqua/*
	@echo "On zip les thèmes"
	cd skins/aqua && zip -q -r ../aqua * -x *svn*

clean:
	-rm bin/*.o
	-rm openalchemist
