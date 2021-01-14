//
// Created by jwarmbier on 28/10/2020.
//

#ifndef QAP_UTILS_H
#define QAP_UTILS_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
using namespace std;

bool ifEnoughArguments(int);
string getPath(int argc, char **argv);

bool ifFileExists(string);

vector<string> splitIntoWords(string line);

int* randomPermutationGenerator(int size);

void runQAPSolver(void (*task)(), double durationSec);


#endif //QAP_UTILS_H
