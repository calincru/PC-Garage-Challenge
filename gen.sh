#!/bin/bash

SAMPLE_CPP=./sample.cpp
OUT_CPP=$1/$1.cpp

mkdir $1
cp $SAMPLE_CPP $OUT_CPP
touch $1/Input$1.txt
touch $1/Output$1.txt

sed -i "s/Input4/Input$1/g" $OUT_CPP
sed -i "s/Output4/Output$1/g" $OUT_CPP
