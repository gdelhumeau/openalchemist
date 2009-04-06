#!/bin/sh
for i in `find -name *.png`
do echo $i; convert -depth 8 $i $i
done
