#!/bin/sh
for i in `find -name *.xml`
do echo $i; rm $i
done
