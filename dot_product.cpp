#include "mpi.h"
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
double* readVector(ifstream& file, int size){
    double* vector = new double[size];
    
    for(int i = 0; i < size; i++){
        file >> vector[i];
    }
    
    return vector;
}

double* readVector(string filename){
    ifstream file (filename.c_str());
    int size;
    file >> size;
    return readVector(file, size);
}

int main(int argc, char** argv){
    /******************************************************
     *                  MPI STUFF BELOW
     ******************************************************/
    if(argc < 3){
        cerr << "Must run as dot_product <VECTOR A FILE> <VECTOR B FILE>"
             << endl;
    }
    MPI_Init(&argc, &argv);
    
    int numProcs, myRank;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
    //Read in a matrix
    double* vectorA = readVector(string(argv[0]));
    
    /******************************************************
     *                    Dot Product
     ******************************************************/
    
    
    
    MPI_Finalize();
}