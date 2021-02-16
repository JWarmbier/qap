//
// Created by jwarmbier on 28/10/2020.
//

#ifndef QAP_QAP_H
#define QAP_QAP_H

#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"
#include "QAPException.h"
#include <sstream>
#include <vector>
#include "algorithm/AlgorithmStrategy.h"

using namespace std;
class AlgorithmStrategy;
class QAP {
    string pathToData;
    string pathToSolution;
    int problemSize;

    int *optimalSolution; // pointer to optimal solution for this instance
    unsigned long long int optimalCost;

    int *solution;
    unsigned long long int cost;

    unsigned long long* flows;
    unsigned long long* distances;

    AlgorithmStrategy * algorithm;

    void getProblemSizeFromFile();

    bool hasAlgorithmFinished;
public:
    QAP(string pathToData, string pathToSolution = "");

    ~QAP();

    void loadData();

    unsigned long long int calculateCost(int* permutation);

    unsigned long long int * getFlows();
    unsigned long long int * getDistances();
    int getProblemSize();

    int getElement(int row, int col);

    string getAlgorithmName();

    void setOptimalSolution(int * foundBestSolution);
    int* getOptimalSolution();
    int* getSolution();

    void setAlgorithmStrategy(AlgorithmStrategy * algorithm);
    void algorithmStep();

    void loadSolutionFromFile(string path);

    long getOptimalCost();
    long getCost();

    bool getHasAlgorithmFinished();
    void resetAlgorithm();

    float optimalSolutionSimilarity();

    long long int getBrowsedSolutionByAlgorithm();
};

#endif //QAP_H
