#!/bin/sh
gcc pl02_02_main.c -o pl02_02_main.o -lm
./pl02_02_main.o 100
cp data/data_02_02_re.csv data/data_02_02_100set.csv
./pl02_02_main.o 1000
cp data/data_02_02_re.csv data/data_02_02_1000set.csv
./pl02_02_main.o 10000
cp data/data_02_02_re.csv data/data_02_02_10000set.csv