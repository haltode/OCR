all: report_1.pdf

report_1.pdf: *.tex
	latexmk -xelatex -shell-escape -pdf report_1.tex

clean:
	rm -rf _minted*
	latexmk -C

full_clean: clean
	rm report_1.pdf
