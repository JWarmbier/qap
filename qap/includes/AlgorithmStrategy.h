//
// Created by jwarmbier on 17/11/2020.
//

#ifndef QAP_ALGORITHMSTRATEGY_H
#define QAP_ALGORITHMSTRATEGY_H

#include <stdlib.h>
#include "neighbourGenerator.h"
#include "utils.h"
#include <string>
#include "QAP.h"

class QAP;

class AlgorithmStrategy {

protected:
    int problemSize;
    int *solution;
    neighbourGenerator *neighbourhood;
    bool hasFinished;
    void initialize();

    long long browsedSolutions;
public:
    AlgorithmStrategy(int problemSizeQAP);
    ~AlgorithmStrategy();

    virtual int* step (QAP * QAPHandler) =0;
    virtual string getName() = 0;
    bool getHasFinished();
    int* getSolution();
    long long getBrowsedSolution();
    void reset();
};

#endif //QAP_ALGORITHMSTRATEGY_H
