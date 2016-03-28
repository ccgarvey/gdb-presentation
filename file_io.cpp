#include "file_io.hpp"

int readSize(std::ifstream& file){
    /*
    * Reads in the size of a file containing vector data.
    * 
    * param: file, an open file offset to the size to read
    * return: the integer size in the file
    */
    int size;
    file >> size;
    return size;
}

double* readVector(std::ifstream& file, int size){
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
    double* vector = new double[size];
    
    for(int i = 0; i < size; i++){
        file >> vector[i];
    }
    
    return vector;
}

void writeOutput(std::ofstream& file, double* vector, int size){
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
    file << size << std::endl;
    for(int i = 0; i < size; i++){
        file << vector[i] << std::endl;
    }
}
