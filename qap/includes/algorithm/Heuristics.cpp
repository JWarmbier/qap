//
// Created by jwarmbier on 24/11/2020.
//

#include "Heuristics.h"

Heuristics::Heuristics(int problemSizeQAP) : AlgorithmStrategy(problemSizeQAP) {
    this->flows = NULL;
    this->distances = NULL;
}

Heuristics::~Heuristics() {
    if(this->flows != NULL)
        delete[] this->flows;
    if(this->distances != NULL)
        delete[] this->distances;
}

string Heuristics::getName() {
    return "Heuristics";
}

int *Heuristics::step(QAP *QAPHandler) {
    this->setDistances(QAPHandler->getFlows());
    this->setFlows(QAPHandler->getDistances());

    fillSolutionWithZeros();
    removesDiagonals();

    while(isZeroInSolution()){
        int maxFlowsIndex = this->findMaxValue(this->flows);

        int maxFlowsIndexRow = maxFlowsIndex / this->problemSize;
        int maxFlowsIndexColumn = maxFlowsIndex % this->problemSize;

        this->removeRowAndColumn(maxFlowsIndexRow, maxFlowsIndexColumn, this->flows);

        int minDistanceIndex = this->findMinValue(this->distances);

        int minDistanceIndexRow = minDistanceIndex / this->problemSize;
        int minDistanceIndexColumn = minDistanceIndex % this->problemSize;

        this->removeRowAndColumn(minDistanceIndexRow, minDistanceIndexColumn, this->distances);

        if(maxFlowsIndexRow != maxFlowsIndexColumn){
            this->solution[minDistanceIndexRow] = maxFlowsIndexRow + 1;
            this->solution[minDistanceIndexColumn] = maxFlowsIndexColumn + 1;
        } else{
            for(int i = 0; i < this->problemSize; i++)
                if(this->solution[i] == 0){
                    this->solution[i] = maxFlowsIndexRow+1;
                    break;
                }
        }
    }

    return solution;
}

int Heuristics::findMaxValue(long long *array) {
    int index = 0;
    for(int i = 1; i < this->problemSize*this->problemSize; i++){
        if(array[index] < array[i])
            index = i;
    }
    return index;
}

int Heuristics::findMinValue(long long int *array) {
    int index = 0, minValue = INT_MAX; //initiated with maximum positive bound

    for(int i = 0; i < this->problemSize*this->problemSize; i++){
        int indexRow = i / this->problemSize;
        int indexColumn = i % this->problemSize;
        if(indexRow != indexColumn){
            if(array[i] > 0 && array[i] < minValue){
                minValue = array[i];
                index = i;
            }
        }
    }
    return index;
}

void Heuristics::fillSolutionWithZeros() {
    for(int i = 0; i < this->problemSize; i++)
        this->solution[i] = 0;
}

void Heuristics::setFlows(unsigned long long int *flows) {
    this->flows = new long long[this->problemSize*this->problemSize];
    for(int i = 0; i < this->problemSize*this->problemSize; i ++)
        this->flows[i] = flows[i];
}

void Heuristics::setDistances(unsigned long long int *distances) {
    this->distances = new long long[this->problemSize*this->problemSize];
    for(int i = 0; i < this->problemSize*this->problemSize; i++)
        this->distances[i] = distances[i];
}

bool Heuristics::isZeroInSolution() {
    for(int i = 0; i < this->problemSize; i++)
        if(this->solution[i] == 0)
            return true;
    return false;
}

void Heuristics::removeRowAndColumn(int indexRow, int indexCol, long long *array) {
    for(int i = 0; i < this->problemSize; i++){
        array[ indexRow*this->problemSize + i] = -1; //removing all elements in row
        array[i*this->problemSize + indexCol] = -1; //removing all elements in column
        //transpose
        array[indexCol*this->problemSize + i] = -1; //removing all elements in row
        array[i*this->problemSize + indexRow] = -1; //removing all elements in column
    }
}

void Heuristics::removesDiagonals() {
    for(int i = 0; i < this->problemSize;i ++){
        this->distances[i*this->problemSize + i] = -1;
        this->flows[i*this->problemSize + i] = -1;
    }
}



