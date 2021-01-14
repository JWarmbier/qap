//
// Created by jwarmbier on 19/11/2020.
//

#ifndef QAP_STEEPEST_H
#define QAP_STEEPEST_H

#include "AlgorithmStrategy.h"

class Steepest : public AlgorithmStrategy {
public:
    Steepest(int problemSizeQAP);
    int* step(QAP * QAPHandler);
    string getName();
};


#endif //QAP_STEEPEST_H
