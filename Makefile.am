
SUBDIRS = \
    src

libdxfdocdir = ${prefix}/doc

libdxfdoc_DATA = \
  README\
  COPYING\
  AUTHORS\
  ChangeLog\
  INSTALL\
  NEWS 

EXTRA_DIST = $(libdxfdoc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
  for specfile in *.spec; do \
    if test -f $$specfile; then \
      cp -p $$specfile $(distdir); \
    fi \
  done
  
