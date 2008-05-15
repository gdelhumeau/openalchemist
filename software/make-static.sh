echo "Making a lib-independant binary"
g++ -o openalchemist-static bin/*.o bin/states/*.o /usr/local/lib/libclanApp.a /usr/local/lib/libclanSDL.a /usr/local/lib/libclanDisplay.a /usr/local/lib/libclanGL.a /usr/local/lib/libclanCore.a /usr/local/lib/libclanSignals.a /usr/lib/libpng.a /usr/lib/libjpeg.a /usr/lib/libz.a /usr/lib/libXmu.a /usr/lib/libXi.a /usr/lib/libXxf86vm.a /usr/lib/libm.a /usr/lib/libGLU.a -lGL `sdl-config --static-libs`  
echo "OK, result on \"openalchemist-static\""
