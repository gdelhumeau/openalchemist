bin_PROGRAMS = openalchemist
openalchemist_SOURCES = src/Application.cpp src/Preferences.cpp src/IniFile.cpp src/GameEngine.cpp src/states/GameState.cpp src/states/CommonState.cpp src/misc.cpp src/CommonResources.cpp src/Player.cpp src/HumanPlayer.cpp src/DemoPlayer.cpp src/Board.cpp src/states/InGameState.cpp src/states/GameOverState.cpp src/ProgressBar.cpp src/states/HighScoreState.cpp src/FrontLayer.cpp src/states/PauseMenuState.cpp src/states/SkinsMenuState.cpp src/Keys.cpp src/states/OptionsMenuState.cpp src/states/TitleState.cpp src/states/QuitMenuState.cpp 
#openalchemist_DATA = skins/aqua.zip data/*

all : skins/aqua.zip skins/brushed.zip skins/vectoriel.zip
static : openalchemist skins/aqua.zip skins/brushed.zip skins/vectoriel.zip
	$(CXX) -o openalchemist-static *.o /usr/local/lib/libclanApp.a /usr/local/lib/libclanSDL.a /usr/local/lib/libclanDisplay.a /usr/local/lib/libclanGL.a /usr/local/lib/libclanCore.a /usr/local/lib/libclanSignals.a /usr/lib/libpng.a /usr/lib/libjpeg.a /usr/lib/libz.a /usr/lib/libXmu.a /usr/lib/libXi.a /usr/lib/libXxf86vm.a /usr/lib/libm.a /usr/lib/libGLU.a -lGL `sdl-config --static-libs`

AM_CXXFLAGS = `pkg-config --cflags clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8`
AM_LDFLAGS = `pkg-config --libs clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8`

skins/aqua.zip : skins/aqua/*
	cd skins/aqua && zip -q -r ../aqua * -x *svn*
skins/brushed.zip : skins/brushed/*
	cd skins/brushed && zip -q -r ../brushed * -x *svn*
skins/vectoriel.zip : skins/vectoriel/*
	cd skins/vectoriel && zip -q -r ../vectoriel * -x *svn*

