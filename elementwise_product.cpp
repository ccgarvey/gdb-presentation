#include <cstdio>
#include "file_io.hpp"

using namespace std;

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
