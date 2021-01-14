//
// Created by jwarmbier on 21/11/2020.
//

#ifndef QAP_RANDOM_H
#define QAP_RANDOM_H

#include "AlgorithmStrategy.h"
#include "utils.h"

class Random : public AlgorithmStrategy{
public:
    Random(int problemSizeQAP);
    int* step(QAP * QAPHandler);
    string getName();
};


#endif //QAP_RANDOM_H
