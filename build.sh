#!/bin/sh

if [ ! -e ./build ]; then
	mkdir build
else
	rm -rf build
	mkdir build
fi

cd ./build

cmake ..

make

cd ..

