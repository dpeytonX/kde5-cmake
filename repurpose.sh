#!/bin/bash

#usage repurpose.sh projectname


sed -i "s/%{APPNAME}/$1/" CMakeLists.txt
sed -i "s/%{APPNAMELC}/$1/" CMakeLists.txt
rm -fr .git
mv 'src/main/%{APPNAMELC}.h.in' "src/main/$1".h.in
sed -i "s/%{APPNAMELC}/$1/" "src/main/$1".h.in
sed -i "s/%{APPNAMELC}/$1/" "src/main/main.cpp"
