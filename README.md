# BVernam: Binary Vernam 

This is the solution of a project for the lecture of System Programming Lab at Bachelor Degree in [Computer Science](https://computerscience.unicam.it) at 
[University of Camerino](https://www.unicam.it). The goal of this project is to implement an adaptation of the 
[Vernam's Cypher](https://en.wikipedia.org/wiki/Gilbert_Vernam). This cypher is a [one-time-pad](https://en.wikipedia.org/wiki/One-time_pad)
based on a simble property of _XOR_ binary operator: 

`(a XOR b) XOR b = c`.

Given a sequence of *k*-bytes b<sub>0</sub>b<sub>1</sub>...b<sub>k-1</sub>, the _key_, the encoding of
any sequence _s_ composed of *N* bytes d<sub>0</sub>d<sub>1</sub>...d<sub>N-1</sub> is obtained by splitting 
the sequence in _K=ceil(N/k)_ blocks of the form D<sub>j</sub>=d<sup>j</sup><sub>0</sub>...d<sup>j</sup><sub>k<sub>j</sub></sub>.
Each block is encoded by applying a _one-time-pad_ and transformed in 
E<sub>j</sub>=e<sup>j</sup><sub>0</sub>...e<sup>j</sup><sub>k<sub>j</sub></sub> where:

e<sup>j</sup><sub>i</sub>=b<sub>(j+i) mod k</sub> XOR d<sup>j</sup><sub>i</sub>

The output sequence is obtained as E<sub>0</sub>...E<sub>ceil(N/k)</sub>.



## Building 

To build the project first of all you have to clone the repository from GitHub:

`git clone https://github.com/michele-loreti/bvernam.git`

This will dowload all the project source files in the folder `bvernam`. 

After that one can use [CMake](https://cmake.org) to generate a Makefile:

`cd bvernam
 cmake ./
 make all`

## Executing

The program `bvernam` takes as input:
1. the file that is use as key;
2. the file to encode;
3. and the where the encoded sequence is stored.

To run program open a console and execute:

`bvernam <keyfile> <inputfile> <outputfile>`

## Tests
A python script is available to test the program on different examples. The script, named `runtests.py`, can be found in 
the folder `python_tests`.

To run the test the following command can be used:

`python3 ./python_tests/runtests.py`





