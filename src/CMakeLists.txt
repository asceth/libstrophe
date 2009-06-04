project(Strophe)

set(HEADER_FILES
  common.h
  hash.h
  md5.h
  ostypes.h
  parser.h
  sasl.h
  sha1.h
  sock.h
  thread.h
  tls.h
  util.h
)

set(SOURCE_FILES
  auth.c
  conn.c
  ctx.c
  event.c
  handler.c
  hash.c
  jid.c
  md5.c
  parser_expat.c
  sasl.c
  sha1.c
  snprintf.c
  sock.c
  stanza.c
  thread.c
  util.c
)

if(APPLE OR UNIX)
  set(PLATFORM_SOURCE_FILES tls_openssl.c)
elseif(WIN32)
  set(PLATFORM_SOURCE_FILES tls_schannel.c)
endif()

set(Strophe_LIBS Expat ssl resolv)

add_library(Strophe ${Strophe_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_SOURCE_FILES})

target_link_libraries(Strophe
  ${Strophe_LIBS}
)

