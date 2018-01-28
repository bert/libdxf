EXTRA_DIST = \
	DXF_R12.xml

.DEFAULT_GOAL : all

all: xmlto

xmlto:
	xmlto html-nochunks *.xml

clean:
	rm -f *.html *~
