#!/bin/sh
./autogen.sh
./configure
make
make -C po update-po
make -C po libdxf.pot
