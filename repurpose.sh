#!/bin/bash

#usage repurpose.sh projectname


sed -i "s/sample/$1/" CMakeLists.txt
rm -fr .git
mv src/main/sample.h.in "src/main/$1".h.in
sed -i "s/sample/$1/" "src/main/$1".h.in
sed -i "s/sample/$1/" "src/main/main.cpp"
