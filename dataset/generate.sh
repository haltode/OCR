#!/bin/bash

fonts=( "Courier" )
charset=( {a..z} {A..Z} {0..9} . , ! ? : \; / + - = \" \' \( \) )
nb_chars=${#charset[@]}

for font in "${fonts[@]}";
do
    mkdir -p train_set/$font
    echo "generating for $font..."

    for (( i=0; i<${nb_chars}; i++ ));
    do
        convert -size 32x32 -font $font -background white -fill black \
                -gravity center -depth 24 -pointsize 25 -compress none \
                label:"${charset[$i]}" -flatten "bmp3:train_set/$font/$i.bmp"
    done
done
