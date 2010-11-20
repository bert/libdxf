
SUBDIRS = \
	src\
	tests
	
libdxfdocdir = ${prefix}/doc

libdxfdoc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS 
	
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
	cd doc; \
	doxygen libDXF-dox-with-call-graphs.dox

.PHONY: apidox-am-yes apidox-am-no apidox

