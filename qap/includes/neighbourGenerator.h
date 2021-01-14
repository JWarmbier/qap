//
// Created by jwarmbier on 17/11/2020.
//

#ifndef QAP_NEIGHBOURGENERATOR_H
#define QAP_NEIGHBOURGENERATOR_H

#include <algorithm>

class neighbourGenerator {
    int permutationLength;
    int *orgPermutation;
    int *currentNeighbour;

    int i, j; //iterators

    void incrementIterators();
public:
    neighbourGenerator(int *permutation, int permutationLength);
    ~neighbourGenerator();

    void setPermutation(int *permutation, int permutationLength);
    int* getOrgPermutation();
    int* Next();
    bool hasNext();

    int* select(int neighbourNumber);
};


#endif //QAP_NEIGHBOURGENERATOR_H
