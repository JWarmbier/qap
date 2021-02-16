//
// Created by jwarmbier on 17/11/2020.
//

#include "AlgorithmStrategy.h"

AlgorithmStrategy::AlgorithmStrategy(int problemSizeQAP){
    this->problemSize = problemSizeQAP;
    this->browsedSolutions = 0;
    this->solution = NULL;
    this->neighbourhood = new neighbourGenerator(this->solution, this->problemSize);

    initialize();

}

AlgorithmStrategy::~AlgorithmStrategy() {
    delete[] this->solution;
}

int *AlgorithmStrategy::getSolution() {
    return this->solution;
}

bool AlgorithmStrategy::getHasFinished() {
    return this->hasFinished;
}

void AlgorithmStrategy::initialize() {
    if(this->solution != NULL)
        delete[] this->solution;

    this->solution = randomPermutationGenerator(this->problemSize);
    this->neighbourhood->setPermutation(this->solution, this->problemSize);

    this->hasFinished = false;
}

void AlgorithmStrategy::reset() {
    initialize(); //reset algorithm
}

long long AlgorithmStrategy::getBrowsedSolution() {
    return this->browsedSolutions;
}

