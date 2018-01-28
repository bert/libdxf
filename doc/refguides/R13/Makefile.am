EXTRA_DIST = \
	DXF_R13.xml

.DEFAULT_GOAL : all

all: xmlto

xmlto:
	xmlto html-nochunks *.xml

clean:
	rm -f *.html *~
