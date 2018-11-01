#!/bin/bash
g++ -std=c++11 KeywordsGenerator.cpp
./a.out
g++ -std=c++11 StringGenerator.cpp
./a.out
g++ -std=c++11 createNFA.cpp
./a.out
g++ -std=c++11 NFAtoDFA.cpp
./a.out
g++ -std=c++11 DFAminimization.cpp
./a.out

