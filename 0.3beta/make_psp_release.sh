#!/bin/sh
mkdir -p PSP/GAME5XX/pspOpenAlchemist
cd src/
make clean
make -f Makefile-3x
echo +++++++++++++++++++++
echo + Copy of PSP files +
echo +++++++++++++++++++++
cp EBOOT.PBP ../PSP/GAME5XX/pspOpenAlchemist
cp pspOpenAlchemist.elf ../PSP/GAME5XX/pspOpenAlchemist
cp pspOpenAlchemist.prx ../PSP/GAME5XX/pspOpenAlchemist
cp PARAM.SFO ../PSP/GAME5XX/pspOpenAlchemist
cd ..
echo ++++++++++++++++++++
echo + Copy of Pictures +
echo ++++++++++++++++++++
cp -R skins PSP/GAME5XX/pspOpenAlchemist
cp -R data  PSP/GAME5XX/pspOpenAlchemist
cp -R graphic PSP/GAME5XX/pspOpenAlchemist
echo ++++++++++++++++++++++
echo + Copy of Properties +
echo ++++++++++++++++++++++
cp highscore-0.3 PSP/GAME5XX/pspOpenAlchemist
cp skins-0.3 PSP/GAME5XX/pspOpenAlchemist
cp preferences-0.3.ini PSP/GAME5XX/pspOpenAlchemist
cp remove_svn.sh PSP/GAME5XX/pspOpenAlchemist
cp remove_xml.sh PSP/GAME5XX/pspOpenAlchemist
echo ++++++++++++++++++++
echo + Remove svn files +
echo ++++++++++++++++++++
cd PSP/GAME5XX/pspOpenAlchemist
sh remove_svn.sh
sh remove_xml.sh
rm remove_svn.sh
rm remove_xml.sh
cd ../../..
echo ++++++++++++++++++++++
echo + Making the archive +
echo ++++++++++++++++++++++
tar -zcvf release/pspOpenAlchemist_0.3beta.zip PSP
#rm -rf PSP
echo done
