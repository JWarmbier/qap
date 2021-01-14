//
// Created by jwarmbier on 21/11/2020.
//

#ifndef QAP_GREEDY_H
#define QAP_GREEDY_H

#include "AlgorithmStrategy.h"

class Greedy : public AlgorithmStrategy{
public:
    Greedy(int problemSizeQAP);
    int* step(QAP * QAPHandler);
    string getName();

};


#endif //QAP_GREEDY_H
