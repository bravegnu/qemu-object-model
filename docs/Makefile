all: oopc.html

class-diagram.png: class-diagram.dia
	dia --export=$@ $<

oopc.html: oopc.asciidoc class-diagram.png
	asciidoc oopc.asciidoc
