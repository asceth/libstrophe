This is strophe, our XMPP client library.

Our goals are:

    * usable quickly
    * well documented
    * reliable

== Build Instructions ==

We use the 'cmake' tool to build the library, unit tests, 
documentation and examples. You'll need to obtain a copy
from http://www.cmake.org/ or from your system distributor.

Once cmake is installed, make a build directory from the
top-level directory and run cmake ..

$ libstrophe> mkdir build
$ libstrophe> cd build
$ libstrophe> cmake ..

This will generate a build system depending on your operating
system.  (makefile, visual studio, xcode, etc).  By default
a dynamic library is built, however you can set the STATIC option
with ccmake or cmake-gui to build a static library.

The library is placed in your libstrophe/build/lib directory.
The public api is defined in <strophe.h> which is also
in the top-level directory.


Currently cmake does not run the test suite.


The examples/ directory contains some examples of how to
use the library; these may be helpful in addition to the
API documentation in doc/.


== Requirements ==

Libstrophe requires libresolv on UNIX systems. Make sure you include -lresolv
if you are compiling by hand.

It also uses expat for XML processing, but a current copy is included in the
expat/ directory of the SVN checkout


