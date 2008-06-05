echo "Install"
echo "----"
./make-package.sh
cp package.tar.gz /
cd /
tar -xf package.tar.gz
rm package.tar.gz
echo "OpenAlchemist is installed !"
