//
// Created by jwarmbier on 24/11/2020.
//

#include "RandomWalk.h"

RandomWalk::RandomWalk(int problemSizeQAP) : AlgorithmStrategy(problemSizeQAP) {

}

int *RandomWalk::step(QAP *QAPHandler) {
    int i, j;

    this->browsedSolutions++;

    i = rand() % this->problemSize;
    j = rand() % this->problemSize;

    if(i == j)
        j = rand() % this->problemSize;

    std::swap(this->solution[i], this->solution[j]);

    return solution;
}

string RandomWalk::getName() {
    return "RandomWalk";
}