#!/bin/sh

mkdir -p m4
libtoolize
aclocal
automake --add-missing --foreign --copy
autoconf
