all:	icefishing.pdf #boost_cmake.pdf

.PHONY : force

force : 

%.pdf : force
	pdflatex -file-line-error -halt-on-error ${@:%.pdf=%.tex}


