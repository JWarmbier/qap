//
// Created by jwarmbier on 17/11/2020.
//

#include "neighbourGenerator.h"


neighbourGenerator::neighbourGenerator(int *permutation, int permutationLength) {
    this->orgPermutation = NULL;
    this->currentNeighbour = NULL;

    this->setPermutation(permutation, permutationLength);
}

int* neighbourGenerator::Next() {
    for(int i = 0; i < this->permutationLength; i++)
        this->currentNeighbour[i] = this->orgPermutation[i];

    std::swap(this->currentNeighbour[this->i], this->currentNeighbour[this->j]); // swap positions i with j

    incrementIterators();

    return currentNeighbour;
}

bool neighbourGenerator::hasNext() {
    return i < this->permutationLength && j < this->permutationLength;
}

void neighbourGenerator::incrementIterators() {
    this->j++;
    if(this->j == this->permutationLength){
        this->i++;
        this->j = this->i + 1;
    }
}

neighbourGenerator::~neighbourGenerator() {
    if(this->orgPermutation != NULL)
        delete[] orgPermutation;
    if(this->currentNeighbour != NULL)
        delete[] currentNeighbour;
}

void neighbourGenerator::setPermutation(int *permutation, int permutationLength) {
    this->permutationLength = permutationLength;

    if(this->currentNeighbour != NULL)
        delete[] this->currentNeighbour;

    this->orgPermutation = permutation;
    this->currentNeighbour = new int[this->permutationLength];

    this->orgPermutation = permutation;

    this->i = 0;
    this->j = this->i + 1;
}

int *neighbourGenerator::getOrgPermutation() {
    return this->orgPermutation;
}

int *neighbourGenerator::select(int neighbourNumber) {

    while(--neighbourNumber)
        incrementIterators();

    return Next();
}




