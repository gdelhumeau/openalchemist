PACKAGES = clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8
LIBS = `pkg-config --libs $(PACKAGES)`
OPTIONS =  -Iincludes -Wall -g
LINKER_OPTIONS =  #-u malloc -lefence
STATIC_LIBS = `pkg-config --libs $(PACKAGES) --static`
CFLAGS = `pkg-config --cflags $(PACKAGES)`

INSTALL_DIR = /usr/local/games/openalchemist

all: test openalchemist
	@echo "OK"

test: 
	@echo "Test dependances installation"
	pkg-config --exists $(PACKAGES)

openalchemist: includes/*.h bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o bin/preferences.o bin/skins-selector.o skins/aqua.zip skins/brushed.zip
	@echo "On assemble le fichier final"
	g++ bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o bin/preferences.o bin/skins-selector.o $(LIBS) -Wall $(LINKER_OPTIONS) -o openalchemist

bin/main.o : includes/*.h src/main.cpp
	g++ -c -o bin/main.o src/main.cpp $(OPTIONS) $(CFLAGS)

bin/game.o: includes/*.h src/game.cpp
	g++ -c -o bin/game.o src/game.cpp $(OPTIONS) $(CFLAGS)

bin/key_events.o : includes/*.h src/key_events.cpp
	g++ -c -o bin/key_events.o src/key_events.cpp  $(OPTIONS) $(CFLAGS)

bin/detect_to_destroy.o : includes/*.h src/detect_to_destroy.cpp
	g++ -c -o bin/detect_to_destroy.o src/detect_to_destroy.cpp $(OPTIONS) $(CFLAGS)

bin/detect_to_fall.o : includes/*.h src/detect_to_fall.cpp
	g++ -c -o bin/detect_to_fall.o src/detect_to_fall.cpp $(OPTIONS) $(CFLAGS)

bin/drawing.o : includes/*.h src/drawing.cpp
	g++ -c -o bin/drawing.o src/drawing.cpp $(OPTIONS) $(CFLAGS)

bin/hightscores.o: includes/*.h src/hightscores.cpp
	g++ -c -o bin/hightscores.o src/hightscores.cpp $(OPTIONS) $(CFLAGS)

bin/pause.o : includes/*.h src/pause.cpp
	g++ -c -o bin/pause.o src/pause.cpp $(OPTIONS) $(CFLAGS)

bin/preferences.o : includes/*.h src/preferences.cpp
	g++ -c -o bin/preferences.o src/preferences.cpp $(OPTIONS) $(CFLAGS)

bin/skins-selector.o : includes/*.h src/skins-selector.cpp
	g++ -c -o bin/skins-selector.o src/skins-selector.cpp $(OPTIONS) $(CFLAGS)

skins/aqua.zip : skins/aqua/*
	@echo "On zip le thème aqua"
	cd skins/aqua && zip -q -r ../aqua * -x *svn*
skins/brushed.zip : skins/brushed/*
	@echo "On zip le thème brushed"
	cd skins/brushed && zip -q -r ../brushed * -x *svn*

clean:
	-rm bin/*.o
	-rm openalchemist
	-rm skins/aqua.zip
	-rm skins/brushed.zip
	
install: openalchemist
	mkdir $(INSTALL_DIR)
	mkdir $(INSTALL_DIR)/skins
	cp openalchemist $(INSTALL_DIR)/
	cp skins/aqua.zip $(INSTALL_DIR)/skins/aqua.zip
	cp skins/brushed.zip $(INSTALL_DIR)/skins/brushed.zip
	ln -s $(INSTALL_DIR)/openalchemist /usr/local/bin/openalchemist

uninstall: $(INSTALL_DIR)
	rm $(INSTALL_DIR)/* -R
	rmdir $(INSTALL_DIR)
	rm /usr/local/bin/openalchemist
	

static: includes/*.h bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o bin/preferences.o bin/skins-selector.o skins/aqua.zip skins/brushed.zip
	@echo "On assemble le fichier final"
	g++ $(STATIC_LIBS) bin/main.o bin/game.o bin/key_events.o bin/detect_to_destroy.o bin/detect_to_fall.o bin/drawing.o bin/hightscores.o bin/pause.o bin/preferences.o bin/skins-selector.o -Wall $(LINKER_OPTIONS) -o openalchemist-static
