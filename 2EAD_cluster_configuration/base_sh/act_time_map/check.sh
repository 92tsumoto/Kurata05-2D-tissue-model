#!/usr/bin/csh

cat ../utype.out | awk '{if(NR==1) print}' > time00.dat
cat time00.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time00.dat.1
awk -f tmp.awk time00.dat >> time00.dat.1

unix2dos *.dat.1

