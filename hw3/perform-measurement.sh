#!/usr/bin/env bash
#Graham Kelly, CSE 374 Assignment 3 Part 1, 4/20/17

if [ $# -lt 1 ]; then
   echo "Insufficient number of arguments passed. Must pass more than one." >&2
   exit 1
fi

URL="$1"
OUTPUT=`mktemp -p '/tmp' -t 'tempXXXXXX' 2> /dev/null`

wget -t 1 -T 5 -o /dev/null -O "$OUTPUT" "$URL" || { echo "0" ; rm "$OUTPUT" 2> /dev/null ; exit 2 ; }

wc -c < "$OUTPUT" || { echo "0" ; rm "$OUTPUT" 2> /dev/null ; exit 3 ; }

rm "$OUTPUT" 2> /dev/null

exit 0
