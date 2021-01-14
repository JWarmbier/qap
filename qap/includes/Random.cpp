//
// Created by jwarmbier on 21/11/2020.
//

#include "Random.h"
Random::Random(int problemSizeQAP) : AlgorithmStrategy(problemSizeQAP) {

}

int *Random::step(QAP * QAPHandler) {
    delete [] this->solution;
    this->solution  = randomPermutationGenerator(this->problemSize);

    this->browsedSolutions++;

    return this->solution;
}

string Random::getName() {
    return "Random";
}


