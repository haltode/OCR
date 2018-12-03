all: report_2.pdf

report_2.pdf: *.tex
	latexmk -xelatex -shell-escape -pdf report_2.tex

clean:
	rm -rf _minted*
	latexmk -C

full_clean: clean
	rm report_2.pdf
