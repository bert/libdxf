# Makefile.am for autogenerating Doxygen developer documentation.

EXTRA_DIST = \
	drakon/*.png \
	drakon/README.md \
	create_libdxf_dox.sh \
	libDXF.dox \
	libDXF-64.png \
	libDXF-96.png \
	libdxf-main.txt \
	hatch.html \
	image.html


doxygen:
if DOXYGEN
	./create_libdxf_dox.sh
else
	@echo "Skipping Doxygen developer documentation generation ..."
endif


.DEFAULT_GOAL : all

all: doxygen

clean:
	-rm -rf *~ html latex

distclean:
	-rm -rf *~ html latex Makefile.in Makefile

