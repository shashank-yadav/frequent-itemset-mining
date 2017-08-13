#!/bin/bash

g++ main.cpp apriori.cpp -std=c++11 -lboost_system -fopenmp -o main
./main $1 $2

