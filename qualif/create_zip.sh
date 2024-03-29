#!/bin/bash

if [ ! -d src ]; then
    echo "Run this from the qualif directory"
    exit 1
fi

cd src
    zip_file="../qualif.zip"
    rm -f "${zip_file}"
    cp ../bin/main.cpp .
    zip "${zip_file}" *.cpp *.cc *.h *.hpp
    rm main.cpp
cd -
