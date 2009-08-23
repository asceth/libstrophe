ACLOCAL_AMFLAGS=-I m4
AUTOMAKE_OPTIONS = subdir-objects

CFLAGS = -g -Wall -Werror

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libstrophe.pc

builtin_CFLAGS = -I$(top_srcdir)/expat/lib
builtin_LIBS = libexpat.la

PARSER_CFLAGS=@PARSER_CFLAGS@
PARSER_LIBS=@PARSER_LIBS@

STROPHE_FLAGS = -I$(top_srcdir)
STROPHE_LIBS = libstrophe.la

## Main build targets
noinst_LTLIBRARIES =

if BUILD_EXPAT
noinst_LTLIBRARIES += libexpat.la
libstrophe_la_DEPENDENCIES = libexpat.la
endif

lib_LTLIBRARIES = libstrophe.la
include_HEADERS = strophe.h strophepp.h

EXTRA_DIST = README.txt CHANGES.txt Doxyfile GPL-LICENSE.txt LICENSE.txt MIT-LICENSE.txt docs vs2008

libstrophe_la_CFLAGS=$(STROPHE_FLAGS) $(PARSER_CFLAGS) $(openssl_CFLAGS)
libstrophe_la_LIBADD = $(PARSER_LIBS) $(openssl_LIBS)
libstrophe_la_SOURCES = src/auth.c src/conn.c src/ctx.c \
	src/event.c src/handler.c src/hash.c \
	src/jid.c src/md5.c src/sasl.c src/sha1.c \
	src/snprintf.c src/sock.c src/stanza.c \
	src/tls_openssl.c src/util.c src/*.h
# ALK: this is not used presently, but causes extra dependency on -lpthread
# libstrophe_la_SOURCES += src/thread.c
if PARSER_EXPAT
libstrophe_la_SOURCES += src/parser_expat.c
else
libstrophe_la_SOURCES += src/parser_libxml2.c
endif

libexpat_la_CFLAGS=-DXML_DTD -DXML_NS -DXML_CONTEXT_BYTES=1024 -DXML_STATIC \
	-I$(top_srcdir)/expat/lib
libexpat_la_SOURCES=expat/lib/xmlparse.c expat/lib/xmltok.c expat/lib/xmlrole.c expat/lib/*.h
EXTRA_DIST += expat

dist-hook:
	rm -rf $(distdir)/expat/.git

## Examples
noinst_PROGRAMS = examples/active examples/roster examples/basic examples/bot
examples_active_SOURCES = examples/active.c
examples_active_CFLAGS = $(STROPHE_FLAGS)
examples_active_LDADD = $(STROPHE_LIBS) 
examples_roster_SOURCES = examples/roster.c
examples_roster_CFLAGS = $(STROPHE_FLAGS)
examples_roster_LDADD = $(STROPHE_LIBS) 
examples_basic_SOURCES = examples/basic.c
examples_basic_CFLAGS = $(STROPHE_FLAGS)
examples_basic_LDADD = $(STROPHE_LIBS) 
examples_bot_SOURCES = examples/bot.c
examples_bot_CFLAGS = $(STROPHE_FLAGS)
examples_bot_LDADD = $(STROPHE_LIBS) 

if HAVE_CHECK

## Tests
TESTS = tests/check_parser tests/check_stanza tests/check_ctx
check_PROGRAMS = tests/check_parser tests/check_stanza tests/check_ctx

tests_check_parser_SOURCES = tests/check_parser.c
tests_check_parser_CFLAGS = @check_CFLAGS@ $(PARSER_CFLAGS) $(STROPHE_FLAGS) \
	-I$(top_srcdir)/src
tests_check_parser_LDADD = @check_LIBS@ $(STROPHE_LIBS)

tests_check_stanza_SOURCES = tests/check_stanza.c
tests_check_stanza_CFLAGS = @check_CFLAGS@ $(PARSER_CFLAGS) $(STROPHE_FLAGS) \
	-I$(top_srcdir)/src
tests_check_stanza_LDADD = @check_LIBS@ $(STROPHE_LIBS)

tests_check_ctx_SOURCES = tests/check_ctx.c
tests_check_ctx_CFLAGS = @check_CFLAGS@ $(PARSER_CFLAGS) $(STROPHE_FLAGS) \
	-I$(top_srcdir)/src
tests_check_ctx_LDADD = @check_LIBS@ $(STROPHE_LIBS)

endif
