#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <fstream>

//#define 0 0

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
    /******************************************************
     *         Initialize MPI and read/split data
     ******************************************************/
    if(argc != 4){
        cerr << "Arguments must be <VECTOR A FILE> <VECTOR B FILE> <OUT FILE>"
             << endl;
        return -1;
    }
    
    MPI_Init(&argc, &argv);
    
    int numProcs, myRank;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
    /* Busy wait! */
    if(myRank == 0){
        bool waitGDB = true;
        while(waitGDB);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    //Read in a matrix
    ifstream fileA (argv[1]);
    ifstream fileB (argv[2]);
    
    double* fullVectorA = NULL;
    double* fullVectorB = NULL; //only matter for root
    
    double* vectorA;
    double* vectorB;
    int size=-1, mySize; //size significant only at root
    if(myRank == 0){
        //Read the sizes
        int sizeA = readSize(fileA);
        int sizeB = readSize(fileB);
        
        if(sizeA != sizeB){
            cerr << "Inconsistent sizes in files. Aborting." << endl;
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
        
        size = sizeA;
        mySize = size/numProcs + size%numProcs;
    }
    
    //Broadcast the size to all processes
    MPI_Bcast((void*) &mySize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Read the vectors and scatter them
    vectorA = new double[mySize];
    vectorB = new double[mySize];
    
    if(myRank == 0){
        fullVectorA = readVector(fileA, size);
    }
    MPI_Scatter((void*) fullVectorA, mySize, MPI_DOUBLE, (void*) vectorA,
                mySize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if(myRank == 0){
        fullVectorB = readVector(fileB, size);
    }
    
    MPI_Scatter((void*) fullVectorB, mySize, MPI_DOUBLE, (void*) vectorB,
                mySize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    
    /******************************************************
     *                    Dot Product
     ******************************************************/
    double* vectorC = new double[mySize];
    for(int i = 0; i < mySize; i++){
        vectorC[i] = vectorA[i]*vectorB[i];
    }
    
    //Free the things we don't need anymore
    delete[] vectorA;
    delete[] vectorB;
    if(myRank == 0){
        delete[] fullVectorA;
        delete[] fullVectorB;
    }
    
    /******************************************************
     *                   Gather Data
     ******************************************************/
    double* fullVectorC;
    if(myRank == 0){
        fullVectorC = new double[size]; 
    }
    
    MPI_Gather((void*) vectorC, mySize, MPI_DOUBLE, (void*) fullVectorC,
               mySize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    /******************************************************
    *                    Store Result
    *******************************************************/
    ofstream fileC (argv[3]);
    if(myRank == 0){
        writeOutput(fileC, fullVectorC, size);
        delete[] fullVectorC;
    }
    
    delete[] vectorC;
    MPI_Finalize();
}