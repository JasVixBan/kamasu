all:	overhead.pdf notes.pdf

.PHONY : force

force : 

%.pdf : force
	test [ -d build ] || mkdir build/
	pdflatex -file-line-error -halt-on-error --output-directory=build ${@:%.pdf=%.tex} 


