#!/bin/bash

aclocal -I /opt/local/share/aclocal
automake --add-missing --foreign --copy
autoconf
