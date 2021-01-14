//
// Created by jwarmbier on 10/11/2020.
//
#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "QAP.h"
#include "AlgorithmStrategy.h"
#include "Greedy.h"
#include "Steepest.h"
#include "Random.h"
#include "utilsForTests.h"
#include "Heuristics.h"

using namespace std;
using testing::Eq;

TEST(QAP, loadDataTest){
    char fileName[] = "sample.txt";
    ofstream MyFile(fileName); // creating File

    int problemSize = 150; // setting up problem size
    long long *flows = new long long[problemSize*problemSize];
    long long *distances = new long long[problemSize*problemSize];

    MyFile << problemSize << endl;

    for(int i = 0; i < problemSize; i++){ //generating flows matrix n^2
        for(int j = 0; j < problemSize; j++){
            flows[i*problemSize +j] = rand()%1000+1;
            MyFile << flows[i*problemSize + j] << " ";
        }
        MyFile << endl;
    }
    MyFile << endl;
    for(int i = 0; i < problemSize; i++){ // generating distances matrix n^2
        for(int j = 0; j < problemSize; j++){
            distances[i*problemSize +j] = rand()%100+1;
            MyFile << distances[i*problemSize + j] << " ";
        }
        MyFile << endl;
    }
    MyFile.close();

    EXPECT_TRUE(ifFileExists(fileName));

    QAP sample(fileName);
    sample.loadData();

    unsigned long long * flowsSample = sample.getFlows();
    unsigned long long * distancesSample = sample.getDistances();

    for(int i = 0; i < problemSize; i++){
        for(int j = 0; j < problemSize; j++){
            EXPECT_EQ(flows[i*problemSize+j], flowsSample[i*problemSize+j]);
            EXPECT_EQ(distances[i*problemSize+j], distancesSample[i*problemSize+j]);
        }
    }
    delete[] flows, distances;
    remove(fileName);
}

TEST(QAP, CalculateCostComplex_1){
    string filename = "../instances/small/data/chr12a.dat";
    QAP sample(filename);

    int permutation[] = {7,  5, 12,  2,  1,  3,  9, 11, 10,  6,  8,  4};

    if(ifFileExists(filename)){
        EXPECT_EQ(9552, sample.calculateCost(permutation));
    } else{
        cout << "Provide file to do tests: " << filename << endl;
    }
}
TEST(QAP, CalculateCostComplex_2){
    string filename = "../instances/small/data/chr12a.dat";
    QAP sample(filename);

    int permutation[] = {7, 5, 12, 2, 1, 3, 9, 11, 10, 6, 8, 4};
    cout << filename << endl;
    if(ifFileExists(filename)){
        EXPECT_EQ(9552, sample.calculateCost(permutation));
    } else{
        cout << "Provide file to do tests: " << filename << endl;
    }
}

TEST(QAP, CalculateCostComplex_3){
    string filename = "../instances/small/data/sko100a.dat";
    QAP sample(filename);

    int permutation[] = {65, 83, 11, 33, 71, 97, 1, 78, 37, 18, 39, 5, 13, 55, 74,
                         95, 25, 63, 79, 91, 27, 80, 54, 94, 75, 31, 43, 14, 77, 6,
                         88, 62, 16, 52, 4, 22, 32, 34, 57, 15, 60, 9, 86, 98, 96,
                         89, 19, 49, 2, 28, 42, 59, 68, 8, 93, 56, 81, 82, 84, 87,
                         10, 24, 40, 67, 85, 30, 73, 51, 69, 20, 58, 70, 66, 100, 26,
                         47, 99, 46, 64, 90, 45, 50, 12, 72, 61, 38, 92, 36, 53, 41,
                         3, 35, 21, 29, 23, 48, 44, 7, 76, 17};
    cout << filename << endl;
    if(ifFileExists(filename)){
        EXPECT_EQ(152002, sample.calculateCost(permutation));
    } else{
        cout << "Provide file to do tests: " << filename << endl;
    }
}

TEST(QAP, getProblemSizeTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(ifFileExists(filename)){
        EXPECT_EQ(26, sample.getProblemSize());
    } else{
        cout << "Provide file to do tests: " << filename << endl;
    }
}

TEST(QAP, setAndGetAlgorithmTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    AlgorithmStrategy* algorithm;
    algorithm = new Steepest(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);
    EXPECT_STREQ(string("Steepest").c_str(), sample.getAlgorithmName().c_str());

    delete algorithm;
    algorithm = new Greedy(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);
    EXPECT_STREQ(string("Greedy").c_str(), sample.getAlgorithmName().c_str());

    delete algorithm;
    algorithm = new Random(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);
    EXPECT_STREQ(string("Random").c_str(), sample.getAlgorithmName().c_str());
}

TEST(QAP, getSolutionTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    AlgorithmStrategy* algorithm;
    algorithm = new Steepest(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);

    int* solution = sample.getSolution();
    assertUniqueAscending(solution, sample.getProblemSize());
}

TEST(QAP, algorithmStepSteepestTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }
    AlgorithmStrategy* algorithm;
    algorithm = new Steepest(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);

    long long previousCost = sample.calculateCost(sample.getSolution());

    while(!sample.getHasAlgorithmFinished()){
        sample.algorithmStep();
        long long cost = sample.calculateCost(sample.getSolution());
        ASSERT_GE(previousCost, cost);
    }
}

TEST(QAP, algorithmStepGreedyTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }
    AlgorithmStrategy* algorithm;
    algorithm = new Greedy(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);

    long long previousCost = sample.calculateCost(sample.getSolution());
    while(!sample.getHasAlgorithmFinished()){
        sample.algorithmStep();
        long long cost = sample.calculateCost(sample.getSolution());
        ASSERT_GE(previousCost, cost);
    }
}

TEST(QAP, algorithmStepHeuristicsTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP sample(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    AlgorithmStrategy* algorithm;
    algorithm = new Heuristics(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);

    long long previousCost = sample.calculateCost(sample.getSolution());
    sample.algorithmStep();

    assertUniqueAscending(sample.getSolution(), sample.getProblemSize());
    cout << "Heuristics cost: " << sample.calculateCost(sample.getSolution()) << endl;
    int * solution = sample.getSolution();
    cout << "Solution: " ;
    for(int i = 0 ; i < sample.getProblemSize(); i ++)
        cout << solution[i] << " " ;
}

TEST(QAP, loadSolutionFromFileTest){
    string filename = "../instances/small/data/bur26a.dat";
    string solution = "../instances/small/data/bur26a.sln";

    QAP sample(filename, solution);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    EXPECT_EQ(5426670, sample.getOptimalCost());
}

TEST(QAP,  GreedyNeighbourhoodTest){
    string filename = "../instances/small/data/bur26a.dat";
    string solution = "../instances/small/data/bur26a.sln";

    QAP sample(filename, solution);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    AlgorithmStrategy* algorithm;
    algorithm = new Greedy(sample.getProblemSize());
    sample.setAlgorithmStrategy(algorithm);

    long long previousCost = sample.calculateCost(sample.getSolution());
    int * previousSolution = new int[sample.getProblemSize()];
    int * currentSolution;

    while(!sample.getHasAlgorithmFinished()){
        currentSolution = sample.getSolution();
        for(int i = 0; i < sample.getProblemSize(); i ++) //store previous solution
            previousSolution[i] = currentSolution[i];

        sample.algorithmStep();
        long long cost = sample.calculateCost(currentSolution);

        ASSERT_GE(previousCost, cost); // check if found better solution

        if(!sample.getHasAlgorithmFinished())
            assertIfNeighbours(currentSolution, previousSolution, sample.getProblemSize());
    }

    delete previousSolution;
}