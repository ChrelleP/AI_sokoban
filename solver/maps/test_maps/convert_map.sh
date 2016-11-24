#!/bin/bash

if grep -q 'X' "$@" 

then
    sed -i '
    s/X/#/g
    s/\./ /g
    s/J/\$/g
    s/G/\./g
    s/M/\@/g
    ' "$@"

else
    sed -i '
    s/#/X/g
    s/\$/J/g
    s/\./G/g
    s/ /\./g
    s/\@/M/g
    ' "$@"
  
fi
