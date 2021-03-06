#include "mpi.h"
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
    /******************************************************
     *         Initialize MPI and read/split data
     ******************************************************/
    const int ROOT = 0;
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
    if(myRank == ROOT){
        bool waitGDB = true;
        while(waitGDB);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    //Read in a vector
    ifstream fileA (argv[1]);
    ifstream fileB (argv[2]);
    
    double* fullVectorA = NULL;
    double* fullVectorB = NULL; //only matter for root
    
    double* vectorA;
    double* vectorB;
    int size=-1, mySize; //size significant only at root
    if(myRank == ROOT){
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
    MPI_Bcast((void*) &mySize, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    
    //Read the vectors and scatter them
    vectorA = new double[mySize];
    vectorB = new double[mySize];
    
    if(myRank == ROOT){
        fullVectorA = readVector(fileA, size);
    }
    MPI_Scatter((void*) fullVectorA, mySize, MPI_DOUBLE, (void*) vectorA,
                mySize, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    
    if(myRank == ROOT){
        fullVectorB = readVector(fileB, size);
    }
    
    MPI_Scatter((void*) fullVectorB, mySize, MPI_DOUBLE, (void*) vectorB,
                mySize, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    
    
    /******************************************************
     *               Elementwise Product
     ******************************************************/
    double* vectorC = new double[mySize];
    for(int i = 0; i < mySize; i++){
        vectorC[i] = vectorA[i]*vectorB[i];
    }
    
    //Free the things we don't need anymore
    delete[] vectorA;
    delete[] vectorB;
    if(myRank == ROOT){
        delete[] fullVectorA;
        delete[] fullVectorB;
    }
    
    /******************************************************
     *                   Gather Data
     ******************************************************/
    double* fullVectorC;
    if(myRank == ROOT){
        fullVectorC = new double[size]; 
    }
    
    MPI_Gather((void*) vectorC, mySize, MPI_DOUBLE, (void*) fullVectorC,
               mySize, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    
    /******************************************************
    *                    Store Result
    *******************************************************/
    ofstream fileC (argv[3]);
    if(myRank == ROOT){
        writeOutput(fileC, fullVectorC, size);
        delete[] fullVectorC;
    }
    
    delete[] vectorC;
    MPI_Finalize();
}
