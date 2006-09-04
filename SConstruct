# OpenAlchemist SCONS file

# IMPORT
import zipfile, os

# CONFIGURATION
FILES = "bin/main.cpp bin/game.cpp bin/detect_to_destroy.cpp bin/detect_to_fall.cpp bin/drawing.cpp bin/hightscores.cpp bin/key_events.cpp bin/preferences.cpp bin/skins-selector.cpp bin/pause.cpp bin/misc.cpp bin/progress_bar.cpp bin/undo.cpp bin/pieces.cpp bin/key.cpp bin/frontlayer.cpp bin/gfx_misc.cpp"
CCFLAGS = "-Wall `pkg-config --cflags clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8`"
CPPPATH = "includes"
LIBS = "pkg-config --libs clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanSDL-0.8"

INCLUDES_TO_CHECK = "vector list ClanLib/core.h ClanLib/application.h ClanLib/gl.h ClanLib/display.h"
LIBS_TO_CHECK = "clanCore clanDisplay clanSignals clanApp clanGL clanSDL"


# CONFIGURING ENVIRONNEMENT
env = Environment()
env.ParseConfig(LIBS)
conf = Configure(env)

# CHECKING LIBRAIRIES
for h in Split(INCLUDES_TO_CHECK):
        if not conf.CheckCXXHeader(h):
                print h+' must be installed!'
                Exit(1)

# CHECKING LIBRAIRIES
for l in Split(LIBS_TO_CHECK):
        if not conf.CheckLib(l):
                print "lib: "+l+' must be installed!'
                Exit(1)


env = conf.Finish()

# BUILIND THE SOFTWARE
BuildDir('bin', 'src')
env.Program('test-scons', Split(FILES), CPPPATH = Split(CPPPATH), CCFLAGS=CCFLAGS)


# FUNCTION TO MAKE ZIP (SKINS)
def zipFile(dir):
        oldpath = os.getcwd()
        f = zipfile.ZipFile(dir+'.zip','w',zipfile.ZIP_DEFLATED)
        os.chdir(dir)
        for root, dirs, files in os.walk('.'):
                if '.sconsign' in files:
                        files.remove('.sconsign')
                
                for afile in files:
                        rroot = root[2:]
                        if not rroot:
                                f.write(afile)
                        else:
                                #print root[2:]+"/"+afile
                                aafile = root[2:]+"/"+afile
                                f.write(aafile)
                
                if '.svn' in dirs:
                        dirs.remove('.svn')  # don't visit SVN directories
        f.close()
        os.chdir(oldpath)
        print dir+" zip created"

# SKINS GENERATION
zipFile('skins/aqua')
zipFile('skins/brushed')
zipFile('skins/vectoriel')



