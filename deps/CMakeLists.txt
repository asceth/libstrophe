project(Expat)

include_directories(${CURRENT_SOURCE_DIR}/expat/lib)

set(SOURCE_FILES
  ${CURRENT_SOURCE_DIR}/expat/lib/xmlparse.c
  ${CURRENT_SOURCE_DIR}/expat/lib/xmltok.c
  ${CURRENT_SOURCE_DIR}/expat/lib/xmlrole.c
)

add_definitions(-DXML_DTD -DXML_NS -DXML_CONTEXT_BYTES=1024 -DXML_STATIC -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_MEMMOVE=1 -DBYTEORDER=4321)

add_library(Expat STATIC ${SOURCE_FILES})


