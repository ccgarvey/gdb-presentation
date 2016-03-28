#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

int readSize(ifstream& file){
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

double* readVector(ifstream& file, int size){
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

void writeOutput(ofstream& file, double* vector, int size){
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
    file << size << endl;
    for(int i = 0; i < size; i++){
        file << vector[i] << endl;
    }
}

int main(int argc, char** argv){
    /*
     * Performs element-wise multiplication of two vectors from two files and
     * outputs the result in an output file.
     * 
     * Three input arguments are required: the filenames for the two input
     * vectors, and the file name for the output vector.
     */
    int size;
    /******************************************************
     *                Read input from files
     ******************************************************/
    if(argc != 4){
        cerr << "Arguments must be <VECTOR A FILE> <VECTOR B FILE> <OUT FILE>"
             << endl;
        return -1;
    }
    
    //Read in a matrix
    ifstream fileA (argv[1]);
    ifstream fileB (argv[2]);
    
    int sizeA = readSize(fileA);
    int sizeB = readSize(fileB);
    
    if(sizeA != sizeB){
        cerr << "Inconsistent sizes in files. Aborting." << endl;
        return -1;
    }
    
    size = sizeA;
    
    double* vectorA = readVector(fileA, size);
    double* vectorB = readVector(fileB, size);
    
    /******************************************************
     *                Element-wise Product
     ******************************************************/
    double* vectorC = new double[size];
    for(int i = 0; i < size; i++){
        vectorC[i] = vectorA[i]*vectorB[i];
    }
    
    //Free the things we don't need anymore
    delete[] vectorA;
    delete[] vectorB;
    
    /******************************************************
    *                    Store Result
    *******************************************************/
    ofstream fileC (argv[3]);
    writeOutput(fileC, vectorC, size);
    
    delete[] vectorC;
}
