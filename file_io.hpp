#ifndef FILE_IO_HPP_
#define FILE_IO_HPP_

#include <fstream>
#include <iostream>
#include <cstdio>

int readSize(std::ifstream& file);
    /*
    * Reads in the size of a file containing vector data.
    * 
    * param: file, an open file offset to the size to read
    * return: the integer size in the file
    */

double* readVector(std::ifstream& file, int size);
    /*
    * Reads in a vector from a file.
    * 
    * The file should have at least size number of elements after the current
    * file offset.
    * 
    * param: file, an open file offset to the elements to read
    * param: size, the number of elements to read
    * return: an array of length size containing elements in the file
    */

void writeOutput(std::ofstream& file, double* vector, int size);
    /*
     * Writes a vector to an output file as follows:
     * size
     * element1
     * element2
     * ...
     * 
     * param: file, an open file to write the vector in
     * param: vector, an array of length at least size to write
     * param: size, the size of the output vector
     */

#endif
