bin_PROGRAMS = openalchemist

openalchemist_SOURCES = ../src/Application.cpp ../src/AudioManager.cpp ../src/Board.cpp ../src/CombosPainter.cpp ../src/CommonResources.cpp ../src/DemoPlayer.cpp ../src/FrameRateCounter.cpp ../src/FrontLayer.cpp ../src/GameEngine.cpp ../src/HumanPlayer.cpp ../src/IniFile.cpp ../src/Keys.cpp ../src/LoadingScreen.cpp ../src/Player.cpp ../src/Preferences.cpp ../src/ProgressBar.cpp ../src/Skin.cpp ../src/SkinsManager.cpp ../src/Window.cpp ../src/main.cpp ../src/memory.cpp ../src/misc.cpp ../src/states/CommonState.cpp ../src/states/GameOverState.cpp ../src/states/GameState.cpp ../src/states/InGameState.cpp ../src/states/MenuState.cpp ../src/states/MenuState/BasicItem.cpp ../src/states/MenuState/DualChoiceItem.cpp ../src/states/MenuState/MenuItem.cpp ../src/states/MenuState/MultipleChoicesItem.cpp ../src/states/MenuState/TableChoicesItem.cpp ../src/states/OptionsMenuState.cpp ../src/states/PauseMenuState.cpp ../src/states/QuitMenuState.cpp ../src/states/SkinsMenuState.cpp ../src/states/TitleState.cpp


AM_CXXFLAGS = `pkg-config --cflags clanCore-2.1 clanDisplay-2.1 clanApp-2.1 clanGL1-2.1 clanGL-2.1 clanGDI-2.1` -DDATA_DIR="\"$(datadir)/openalchemist\""
AM_LDFLAGS = `pkg-config --libs clanCore-2.1 clanDisplay-2.1 clanApp-2.1 clanGL1-2.1 clanGL-2.1 clanGDI-2.1 clanSound-2.1 clanVorbis-2.1`
