xml_SOURCES := $(wildcard *.xml)

html_TARGETS := $(patsubst %.xml,%.html,$(xml_SOURCES))

%.html: %.xml
	xmlto html-nochunks $<

.DEFAULT_GOAL := all

all: \
	$(html_TARGETS)

clean:
	rm -f *.html *~

