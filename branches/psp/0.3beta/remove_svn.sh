#!/bin/sh
for i in `find -name .svn`
do echo $i; rm -rf $i
done
