#!/bin/bash

xelatex lorem_ipsum.tex
mkdir -p courier
pdftoppm lorem_ipsum.pdf courier/lorem_ipsum -png -rx 300 -ry 300
