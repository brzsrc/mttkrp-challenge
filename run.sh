#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Debug ./
make
./mttkrp -d -1 -i ./tensors/vast-2015-mc1-5d.tns -o output.txt -v validOutput.txt