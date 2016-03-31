#!/bin/sh
make distclean
#autoreconf
./autogen.sh
./configure
make
make -C po update-po
make -C po libdxf.pot
#../cppcheck/cppcheck -I ./src -f --enable=all ./ 2>libdxf_error.txt
