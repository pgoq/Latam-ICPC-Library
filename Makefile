LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds las4s e pelados ICPC library"
	@echo ""
	@echo "Available commands are:"
	@echo "	make las4s		- to build las4s"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove las4s.pdf"
	@echo "	make help		- to show this information"
	@echo ""

las4s: test-session.pdf | build
	touch aux.cpp
	$(LATEXCMD) content/las4s.tex && $(LATEXCMD) content/las4s.tex
	cp build/las4s.pdf las4s.pdf
	rm aux.cpp

clean:
	cd build && rm -f las4s.aux las4s.log las4s.tmp las4s.toc las4s.pdf las4s.ptc

veryclean: clean
	rm -f las4s.pdf test-session.pdf

.PHONY: help fast las4s clean veryclean

build:
	mkdir -p build/


test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf