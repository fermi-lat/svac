
%.ps : %.dot
	dot -Tps -o$@ $<

%.bmp : %.ps
	gs -r600 -sOutputFile=$@ -sDEVICE=bmpmono -dBATCH -dNOPAUSE $<

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
BMPFILES=desired-EM2-v1r0.bmp actual-EM2-v1r0.bmp newlaunch-EM2-v1r0.bmp desired-EM2-v2r0.bmp

IAndTPipeline.pdf: IAndTPipeline.ps

IAndTPipeline.ps: IAndTPipeline.tex $(EPSFILES)

clean:
	rm -f *.ps *.eps *.pdf *.aux *.dvi *.log *.gif *.bmp web

bmp: $(BMPFILES)
	touch $@

web: $(BMPFILES) IAndTPipeline.pdf
	cp $? /u/ek/focke/public_html/pipeline
	touch web
