#!/bin/bash

fonts=( "courier" "dejavu_sans" )

python3 generate_scrambled.py
echo

for font in "${fonts[@]}";
do
    mkdir -p $font
    echo "generating '$font' font dataset..."

    pdflatex $font.tex > /dev/null
    pdftoppm $font.pdf $font/page -png -rx 300 -ry 300
done
