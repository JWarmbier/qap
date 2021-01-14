//
// Created by jwarmbier on 23/11/2020.
//

#ifndef QAP_UTILSFORTESTS_H
#define QAP_UTILSFORTESTS_H
#include <gtest/gtest.h>
#include <iostream>
using namespace std;
using testing::Eq;

void assertUniqueAscending(int *array, int size);

void printPermutation(int * permutation, int size);
void assertIfNeighbours(int * expected, int * actual, int size);
#endif //QAP_UTILSFORTESTS_H
