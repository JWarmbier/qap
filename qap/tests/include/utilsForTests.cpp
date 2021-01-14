//
// Created by jwarmbier on 23/11/2020.
//

#include "utilsForTests.h"
void assertUniqueAscending(int *array, int size){
    bool *truthTable = new bool[size];
    for(int i = 0;i < size; i++)
        truthTable[i] = false;

    for(int i = 0; i < size ; i++)
        truthTable[array[i]-1] = true;

    for(int i = 0; i < size; i++)
        ASSERT_TRUE(truthTable[i]);

    delete [] truthTable;
}

void printPermutation(int * permutation, int size){
    cout << "Permutation: ";
    for(int i = 0; i < size; i++){
        cout << permutation[i] << " ";
    }
}

void assertIfNeighbours(int * expected, int * actual, int size){
    int twoOPT = 0;
    for(int i = 0; i < size; i++)
        if(expected[i] != actual[i])
            twoOPT++;
    if(twoOPT == 0)
        std::cout << "Takie same: " << twoOPT << endl;
    ASSERT_EQ(2, twoOPT); //only two places are not correect
}