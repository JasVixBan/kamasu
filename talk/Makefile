all:	overhead.pdf notes.pdf

.PHONY : force

force : 

%.pdf : force
	pdflatex -file-line-error -halt-on-error --output-directory=build ${@:%.pdf=%.tex} 

clean:
	rm build/*


