//
// Created by jwarmbier on 24/11/2020.
//

#ifndef QAP_HEURISTICS_H
#define QAP_HEURISTICS_H

#include "AlgorithmStrategy.h"
#include "QAP.h"
#include <bits/stdc++.h>

class QAP;

class Heuristics :public  AlgorithmStrategy{
    int findMaxValue(long long * array);
    int findMinValue(long long int *array);

    void setFlows(unsigned long long int *flows);
    void setDistances(unsigned long long int *distances);
    void removeRowAndColumn(int indexRow, int indexCol, long long *array);
    void removesDiagonals();

    bool isZeroInSolution();

    void fillSolutionWithZeros();
    long long * flows;
    long long * distances;
public:
    Heuristics(int problemSizeQAP);
    ~Heuristics();
    int* step(QAP * QAPHandler);
    string getName();
};

#endif //QAP_HEURISTICS_H
