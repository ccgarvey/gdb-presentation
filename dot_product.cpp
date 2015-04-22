#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Reads in a vector from a file.
 * 
 * File must be formatted so that the first number in it is an integer
 * indicating how large the vector is, followed by double values.
 * 
 * param: filename, the name of the file to load
 * return: an 
 */

int readSize(ifstream& file){
    int size;
    file >> size;
    return size;
}

double* readVector(ifstream& file, int size){
    double* vector = new double[size];
    
    for(int i = 0; i < size; i++){
        file >> vector[i];
    }
    
    return vector;
}

void writeOutput(ofstream& file, double* vector, int size){
    file << size << endl;
    for(int i = 0; i < size; i++){
        file << vector[i] << endl;
    }
}

int main(int argc, char** argv){
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
    
    double* vectorA = readVector(fileA, size);
    double* vectorB = readVector(fileB, size);
    
    /******************************************************
     *                    Dot Product
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