//
// Created by jwarmbier on 21/11/2020.
//

#include "Greedy.h"
#include <fstream>
int* Greedy::step(QAP * QAPHandler) {
    neighbourhood->setPermutation(this->solution, this->problemSize);
    ofstream myfile;

    long lastCost = QAPHandler->calculateCost(this->solution);

    while(neighbourhood->hasNext()){
        this->browsedSolutions++;
        int *nextNeighbour = neighbourhood->Next();
        if(QAPHandler->calculateCost(nextNeighbour) < lastCost){
            for(int i = 0; i < this->problemSize; i++)
                this->solution[i] = nextNeighbour[i];

            return this->solution; // return first better solution
        }
    }

    this->hasFinished = true;
    return this->solution;
}

string Greedy::getName() {
    return "Greedy";
}

Greedy::Greedy(int problemSizeQAP) : AlgorithmStrategy(problemSizeQAP) {
    this->hasFinished = false;
}


