#!/bin/bash
# download boost
echo 'downloading boost...'
boost=$(wget -O boost_1_73_0.tar.gz https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.gz)
tar -xvf boost_1_73_0.tar.gz
cd boost_1_73_0

# install boost
echo 'installing boost...'
./bootstrap.sh --prefix=/DERAS-Server/DERAS-Server/lib
./b2
sudo ./b2 install

# install mysql c++ connector
cd ../
git clone https://github.com/mysql/mysql-connector-cpp
cd mysql-connector-cpp
locate -i /boost/version.hpp
cmake . -DBOOST_ROOT=../DERAS-Server/DERAS-Server/include/boost/
cmake .
make clean
make
make install
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/usr/local/mysql/connector-c++-/lib64/debug'
