
%.ps : %.dot
	dot -Tps -o$@ $<

%.eps : %.ps
	ps2eps $< $@

%.ps : %.dvi
	dvips -o $@ $<

%.dvi : %.tex
	latex $<
	latex $<

%.pdf : %.ps
	ps2pdf $< $@

IAndTPipeline.pdf: IAndTPipeline.ps

IAndTPipeline.ps: IAndTPipeline.tex desired-EM2-v1r0.eps actual-EM2-v1r0.eps

clean:
	rm -f *.ps *.eps *.pdf *.aux *.dvi *.log
