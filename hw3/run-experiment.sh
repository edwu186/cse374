#!/usr/bin/env bash
#Graham Kelly, CSE 374 Assignment 3 Part 3, 4/20/2017

if [ $# -lt 2 ]; then
   echo "Insufficient number of arguments passed. Must pass at least 2." >&2
   exit 1
fi

if [ ! -e "$1" ]; then
   echo "Input file $1 does not exist. Please pass a valid filename." >&2
   exit 1
fi

INPUT="$1"
OUTPUT="$2"
let RANK=0

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Performing measurement on $line"
    let RANK=RANK+1
    let SIZE=`./perform-measurement.sh "$line"`
    if [ $SIZE -gt 0 ]; then
	echo "...success"
	echo "$RANK $line $SIZE" >> "$OUTPUT"
    else
	echo "...failed"
    fi
done < "$INPUT"

exit 0