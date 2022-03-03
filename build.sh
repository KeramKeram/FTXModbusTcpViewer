rm -rf bin
mkdir bin
cp configuration.json bin/
cd bin
cmake ..
make -j4
cp src/App/FTXModbusTcpViewer .