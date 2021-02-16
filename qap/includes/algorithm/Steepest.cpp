//
// Created by jwarmbier on 19/11/2020.
//

#include "Steepest.h"

int* Steepest::step(QAP * QAPHandler) {
    int *bestPermutation = new int[this->problemSize];
    int bestCost;
    bool foundBetter = false;

    for(int i = 0; i < this->problemSize; i++) //rewrite solution from last step
        bestPermutation[i] = this->solution[i];

    bestCost = QAPHandler->calculateCost(bestPermutation);

    neighbourhood->setPermutation(this->solution, this->problemSize);

    while(neighbourhood->hasNext()){
        this->browsedSolutions++;
        int *nextNeighbour = neighbourhood->Next();
        if(QAPHandler->calculateCost(nextNeighbour) < bestCost){
            for(int i = 0; i < this->problemSize; i++)
                bestPermutation[i] = nextNeighbour[i];
            bestCost = QAPHandler->calculateCost(bestPermutation);
            foundBetter = true;
        }
    }

    for(int i = 0; i < this->problemSize; i++) //set chosen solution in this step
        solution[i] = bestPermutation[i];

    this->hasFinished = !foundBetter;
    delete[] bestPermutation;

    return solution;
}

string Steepest::getName() {
    return "Steepest";
}

Steepest::Steepest(int problemSizeQAP) : AlgorithmStrategy(problemSizeQAP) {

}
