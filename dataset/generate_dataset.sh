#!/bin/sh

python3 generate_scrambled.py
pdflatex courier.tex
mkdir -p courier
pdftoppm courier.pdf courier/page -png -rx 300 -ry 300
