
ACLOCAL_AMFLAGS = `-I m4` 

SUBDIRS = \
	doc \
	po \
	src \
	tests
	
libdxfdocdir = ${prefix}/doc

libdxfdoc_DATA = \
	ABOUT-NLS \
	AUTHORS \
	ChangeLog \
	CODE_OF_CONDUCT.md \
	CONTRIBUTING \
	COPYING \
	INSTALL \
	LICENSE \
	NEWS \
	README \
	doc/AUTHORS.md \
	doc/BUGS.md \
	doc/DEPENDENCIES.md \
	doc/ISSUES.md \
	doc/MANIFEST \
	doc/TODO
	
EXTRA_DIST = $(libdxfdoc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
	
## generate API documentation with doxygen
apidox:
	$(MAKE) apidox-am-@LIBDXF_HAS_DOXYGEN@

apidox-am-no:
apidox-am-yes:
	@echo "*** Creating API documentation main page"; \
	cd doc/doxygen; \
	doxygen libDXF.dox

.PHONY: apidox-am-yes apidox-am-no apidox

