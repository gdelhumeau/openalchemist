SUBDIRS = build

dist_pkgdata_DATA = skins/aqua skins/brushed skins/vectoriel data/* CODE-LICENSE GRAPHICS-LICENSE

all : skins/aqua.zip skins/brushed.zip skins/vectoriel.zip openalchemist
static : openalchemist skins/aqua.zip skins/brushed.zip skins/vectoriel.zip
	$(CXX) -o openalchemist-static *.o /usr/local/lib/libclanApp.a /usr/local/lib/libclanSDL.a /usr/local/lib/libclanDisplay.a /usr/local/lib/libclanGL.a /usr/local/lib/libclanCore.a /usr/local/lib/libclanSignals.a /usr/lib/libpng.a /usr/lib/libjpeg.a /usr/lib/libz.a /usr/lib/libXmu.a /usr/lib/libXi.a /usr/lib/libXxf86vm.a /usr/lib/libm.a /usr/lib/libGLU.a -lGL `sdl-config --static-libs`

openalchemist: build/openalchemist
	cp build/openalchemist openalchemist

skins/aqua.zip : skins/aqua/*
	cd skins/aqua && zip -q -r ../aqua * -x *svn*
skins/brushed.zip : skins/brushed/*
	cd skins/brushed && zip -q -r ../brushed * -x *svn*
skins/vectoriel.zip : skins/vectoriel/*
	cd skins/vectoriel && zip -q -r ../vectoriel * -x *svn*

CLEANFILES = skins/*.zip openalchemist

