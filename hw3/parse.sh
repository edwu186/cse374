#!/usr/bin/env bash
#Graham Kelly, CSE 374 Assignment 3 Part 2, 4/20/2017

if [ $# -lt 2 ]; then
   echo "Insufficient number of arguments passed. Must pass at least two." >&2
   exit 1
fi

if [ ! -e "$1" ]; then
   echo "Input file $1 does not exist. Please pass a valid filename." >&2
   exit 1
fi

INPUT="$1"
OUTPUT="$2"

grep -Eoi '<strong><a [^>]+>' "$INPUT" | grep -Eo 'href="[^\"]+"' |  grep -Eo '(http|https)://[^/"]+' > "$OUTPUT"

exit 0
