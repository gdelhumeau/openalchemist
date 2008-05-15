echo "Make a package"
echo "----"
echo "Compiling"
scons
#./make-static.sh
echo "Making folders"
mkdir package/
mkdir package/usr
mkdir package/usr/local
mkdir package/usr/local/games
mkdir package/usr/local/games/openalchemist
mkdir package/usr/local/games/openalchemist/skins
mkdir package/usr/local/games/openalchemist/data
mkdir package/usr/local/bin
echo "Copying files"
cp skins/*.zip package/usr/local/games/openalchemist/skins
cp data/loading.png package/usr/local/games/openalchemist/data/
cp openalchemist package/usr/local/games/openalchemist/
#cp openalchemist-static package/usr/local/games/openalchemist/
cp config.py package/usr/local/games/openalchemist/
cp openalchemist-config package/usr/local/games/openalchemist/
echo "Making links"
ln -s /usr/local/games/openalchemist/openalchemist package/usr/local/bin/openalchemist
echo "#!/bin/sh" >  package/usr/local/bin/openalchemist-config
echo "python /usr/local/games/openalchemist/config.py" >>  package/usr/local/bin/openalchemist-config
chmod u+x package/usr/local/bin/openalchemist-config
cd package
tar -czf ../package.tar.gz *
cd ..
rm package -R
echo "Look at \"package.tar.gz\" file !"
