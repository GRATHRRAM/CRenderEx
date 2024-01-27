#!/bin/bash
cd src/
gcc -Wall -g -c CRenderEx.c -o CRenderEx.o
gcc -Wall -g -c CRInput.c -o CRInput.o
ar ruv libCRenderEx.a CRenderEx.o
ar ruv libCRInput.a CRInput.o
ranlib libCRenderEx.a
ranlib libCRInput.a
cd ..
mkdir Build
cp src/*.a Build/
rm src/*.a src/*.o
