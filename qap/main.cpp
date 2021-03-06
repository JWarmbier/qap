//
// Created by jwarmbier on 28/10/2020.
//
#include <string>
#include <iostream>
#include "includes/utils.h"
#include <chrono>
#include "algorithm/Steepest.h"
#include "algorithm/Greedy.h"
#include "algorithm/RandomWalk.h"
#include "algorithm/Random.h"
#include "algorithm/Heuristics.h"
#include <gtest/gtest.h>
#include "QAP.h"
#include <filesystem>
#include <fstream>
#define RESULTS_PATH "../results/"

namespace fs = filesystem;

using namespace std;
using namespace std::chrono;

bool createFolderForResults(string dataName){
    fs::create_directories(RESULTS_PATH + dataName);
}

void runSolverInConstantTime(QAP * handler, double durationTime, string resultDirectory){
    ofstream myfile;
    resultDirectory += "/" + handler->getAlgorithmName();

    myfile.open(resultDirectory);

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    high_resolution_clock::time_point endTime;

    do{
        handler->algorithmStep();
        if(handler->getHasAlgorithmFinished())
            myfile << (double)handler->getCost() << endl;
    } while (duration_cast<duration<double>>(high_resolution_clock::now() - startTime).count() < durationTime);
    myfile << "time:" << duration_cast<duration<double>>(high_resolution_clock::now() - startTime).count() << endl;
    myfile << "browsedSolutions:" << handler->getBrowsedSolutionByAlgorithm() << endl;
}

void runSolverNumberOfRuns(QAP * handler, double numberOfRuns, string resultDirectory){
    ofstream myfile;
    resultDirectory += "/" + handler->getAlgorithmName();

    myfile.open(resultDirectory);

    int counter = 0;
    int steps = 0;
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    high_resolution_clock::time_point endTime;

    while(counter < numberOfRuns){
        steps++;
        handler->algorithmStep();
        if(handler->getHasAlgorithmFinished()){
            myfile << (double)handler->getCost() << endl;
            myfile << "steps:" << steps << endl;
            counter++;
            steps = 0;
        }

    }
    myfile << "time:" << duration_cast<duration<double>>(high_resolution_clock::now() - startTime).count() << endl;
    myfile << "browsedSolutions:" << handler->getBrowsedSolutionByAlgorithm() << endl;
}

void endsRunSolver(QAP * handler, string resultDirectory){
    ofstream myfile;
    resultDirectory += "/" + handler->getAlgorithmName();

    myfile.open(resultDirectory);

    for(int i = 0; i < 400; i++){

        while(!handler->getHasAlgorithmFinished()){
            handler->algorithmStep();
        }

        myfile << (double)handler->getCost() << endl;
        handler->algorithmStep();
    }
}
void beginingEndRunSolver(QAP * handler, string resultDirectory, AlgorithmStrategy* algorithm){
    ofstream myfile;
    resultDirectory += "/" + handler->getAlgorithmName();

    myfile.open(resultDirectory);

    for(int i = 0; i < 250; i++){
        if( i == 0){
            myfile << (double)handler->calculateCost(algorithm->getSolution()) << " ";
        }
        while(!handler->getHasAlgorithmFinished()){
            handler->algorithmStep();
        }
        if (i != 0)
            myfile << (double)handler->calculateCost(algorithm->getSolution()) << " ";

        myfile << (double)handler->getCost() << endl;
        handler->algorithmStep();
    }
}

void qualityRunSolver(QAP * handler, string resultDirectory, AlgorithmStrategy* algorithm){
    ofstream myfile;
    resultDirectory += "/" + handler->getAlgorithmName();

    myfile.open(resultDirectory);

    for(int i = 0; i < 100; i++){

        while(!handler->getHasAlgorithmFinished()){
            handler->algorithmStep();
        }

        myfile << ((double)handler->getCost()- (double)handler->getOptimalCost())/(double)handler->getOptimalCost() ;
        myfile << " " << handler->optimalSolutionSimilarity() << endl;
        handler->algorithmStep();
    }
}

void doTests(string filename, string solution, string dataName, double timeTakenByAlgorithmSec){

    string browsedSolution = RESULTS_PATH + string("/browsedSolution/");
    ofstream file;

    createFolderForResults(dataName);
    createFolderForResults("/browsedSolution/" + dataName);

    QAP *qapHandler= new QAP(filename, solution);


    AlgorithmStrategy* algorithm;
//
//    file.open(browsedSolution + dataName + "/Greedy");
    algorithm = new Greedy(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);

    //Greedy
    string resultDirectory = RESULTS_PATH + dataName;
//    runSolverNumberOfRuns(qapHandler,10, resultDirectory);
//
    file << algorithm->getBrowsedSolution() << endl;
    file.close();

    //RandomWalk
    file.open(browsedSolution + dataName + "/RandomWalk");
    delete algorithm;
    algorithm = new RandomWalk(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    runSolverInConstantTime(qapHandler,timeTakenByAlgorithmSec, resultDirectory);

    file << algorithm->getBrowsedSolution() << endl;
    file.close();

    //Steepest
    file.open(browsedSolution + dataName + "/Steepest");
    delete algorithm;
    algorithm = new Steepest(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    runSolverNumberOfRuns(qapHandler,10, resultDirectory);

    file << algorithm->getBrowsedSolution() << endl;
    file.close();

    // Random
    file.open(browsedSolution + dataName + "/Random");
    delete algorithm;
    algorithm = new Random(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    runSolverInConstantTime(qapHandler,timeTakenByAlgorithmSec, resultDirectory);

    file << algorithm->getBrowsedSolution() << endl;
    file.close();

    //Heuristics
    delete algorithm;
    algorithm = new Heuristics(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    file.open(resultDirectory + "/" + qapHandler->getAlgorithmName());

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    high_resolution_clock::time_point endTime;
    qapHandler->algorithmStep();
    file << "time:" << duration_cast<duration<double>>(high_resolution_clock::now() - startTime).count() << endl;
    file << qapHandler->getCost() << endl;
    file.close();

    delete qapHandler;
}

void compareBeginingsWithEnds(string filename, string solution, string dataName, int timeTakenByAlgorithmSec){

    string browsedSolution = RESULTS_PATH + string("/beginningEnd/");

    createFolderForResults(dataName);
    createFolderForResults("/beginningEnd/" + dataName);

    QAP *qapHandler= new QAP(filename, solution);

    AlgorithmStrategy* algorithm;
    algorithm = new Greedy(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);


    string resultDirectory = RESULTS_PATH + dataName;
    beginingEndRunSolver(qapHandler, browsedSolution + dataName, algorithm);


    delete algorithm;
    algorithm = new Steepest(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    beginingEndRunSolver(qapHandler, browsedSolution + dataName, algorithm);


    delete qapHandler;

}

void compareEnds(string filename, string solution, string dataName, int timeTakenByAlgorithmSec){
    string browsedSolution = RESULTS_PATH + string("/ends/");

    createFolderForResults(dataName);
    createFolderForResults("/ends/" + dataName);

    QAP *qapHandler= new QAP(filename, solution);

    AlgorithmStrategy* algorithm;
    algorithm = new Greedy(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);


    string resultDirectory = RESULTS_PATH + dataName;
    endsRunSolver(qapHandler, browsedSolution + dataName);


    delete algorithm;
    algorithm = new Steepest(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    endsRunSolver(qapHandler, browsedSolution + dataName);


    delete qapHandler;
}

void qualityProximitySolution(string filename, string solution, string dataName, int timeTakenByAlgorithmSec){

    string browsedSolution = RESULTS_PATH + string("/quality/");

    createFolderForResults(dataName);
    createFolderForResults("/quality/" + dataName);

    QAP *qapHandler= new QAP(filename, solution);

    AlgorithmStrategy* algorithm;
    algorithm = new Greedy(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    string resultDirectory = RESULTS_PATH + dataName;
    qualityRunSolver(qapHandler, browsedSolution + dataName, algorithm);


    delete algorithm;
    algorithm = new Steepest(qapHandler->getProblemSize());
    qapHandler->setAlgorithmStrategy(algorithm);
    qualityRunSolver(qapHandler, browsedSolution + dataName, algorithm);

    delete qapHandler;

}

int main(int argc, char *argv[]){
//    doTests("../instances/small/data/chr25a.dat", "../instances/small/data/chr25a.sln", "chr25a", 3.12206);
//    doTests("../instances/small/data/nug25.dat", "../instances/small/data/nug25.sln", "nug25", 2.79817);
//    doTests("../instances/small/data/nug27.dat", "../instances/small/data/nug27.sln", "nug27", 4.31772);
//    doTests("../instances/small/data/bur26a.dat", "../instances/small/data/bur26a.sln", "bur26a", 4.98288);
//    doTests("../instances/small/data/chr12a.dat", "../instances/small/data/chr12a.sln", "chr12a", 0.186);
//    doTests("../instances/small/data/tai50b.dat", "../instances/small/data/tai50b.sln", "tai50b", 85.2709);
//    doTests("../instances/small/data/lipa50a.dat", "../instances/small/data/lipa50a.sln", "lipa50a", 45.3639);
//    doTests("../instances/small/data/lipa50b.dat", "../instances/small/data/lipa50b.sln", "lipa50b", 56.3112);

//    compareBeginingsWithEnds("../instances/small/data/chr25a.dat", "../instances/small/data/chr25a.sln", "chr25a", 10);
//    compareBeginingsWithEnds("../instances/small/data/nug25.dat", "../instances/small/data/nug25.sln", "nug25", 10);
//    compareBeginingsWithEnds("../instances/small/data/nug27.dat", "../instances/small/data/nug27.sln", "nug27", 10);
//    compareBeginingsWithEnds("../instances/small/data/bur26a.dat", "../instances/small/data/bur26a.sln", "bur26a", 10);

//    compareEnds("../instances/small/data/nug27.dat", "../instances/small/data/nug27.sln", "nug27", 10);
//    compareEnds("../instances/small/data/bur26a.dat", "../instances/small/data/bur26a.sln", "bur26a", 10);

//    qualityProximitySolution("../instances/small/data/nug27.dat", "../instances/small/data/nug27.sln", "nug27", 10);
//    qualityProximitySolution("../instances/small/data/chr25a.dat", "../instances/small/data/chr25a.sln", "chr25a", 10);

//    testing::InitGoogleTest();
//    RUN_ALL_TESTS();

    return  0;
}


