#!/bin/sh
./autogen.sh
./configure --disable-doc
make
make -C po update-po
make -C po libdxf.pot
