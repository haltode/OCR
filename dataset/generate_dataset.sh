#!/bin/bash

fonts=( "liberation_sans" "liberation_serif" "liberation_mono" )

python3 generate_scrambled.py
echo

for font in "${fonts[@]}";
do
    mkdir -p $font
    echo "generating '$font' font dataset..."

    xelatex $font.tex > /dev/null
    pdftoppm $font.pdf $font/page -png -rx 300 -ry 300
done
