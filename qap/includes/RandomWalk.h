//
// Created by jwarmbier on 24/11/2020.
//

#ifndef QAP_RANDOMWALK_H
#define QAP_RANDOMWALK_H
#include "AlgorithmStrategy.h"

class QAP;

class RandomWalk : public AlgorithmStrategy{
public:
    RandomWalk(int problemSizeQAP);
    int* step(QAP * QAPHandler);
    string getName();
};


#endif //QAP_RANDOMWALK_H
