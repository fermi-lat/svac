
%.ps : %.dot
	dot -Tps -o$@ $<

%.gif : %.dot
	dot -Tgif -o$@ $<

%.eps : %.ps
	ps2eps $< $@

%.ps : %.dvi
	dvips -o $@ $<

%.dvi : %.tex
	latex $<
	latex $<

%.pdf : %.ps
	ps2pdf $< $@

EPSFILES=desired-EM2-v1r0.eps actual-EM2-v1r0.eps newlaunch-EM2-v1r0.eps
GIFFILES=desired-EM2-v1r0.gif actual-EM2-v1r0.gif newlaunch-EM2-v1r0.gif

IAndTPipeline.pdf: IAndTPipeline.ps

IAndTPipeline.ps: IAndTPipeline.tex $(EPSFILES)

clean:
	rm -f *.ps *.eps *.pdf *.aux *.dvi *.log *.gif web

web: $(GIFFILES) IAndTPipeline.pdf
	cp $? /u/ek/focke/public_html/pipeline
	touch web
