//
// Created by jwarmbier on 17/11/2020.
//
#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "algorithm/AlgorithmStrategy.h"
#include "algorithm/Greedy.h"
#include "algorithm/Steepest.h"
#include "algorithm/Random.h"

#include <vector>
#include <stdlib.h>

TEST(AlgorithmStrategy, pointerTests){
    AlgorithmStrategy * algorithmPointer;

    algorithmPointer = new Greedy(10);

    char greedyStr[] = "Greedy";
    EXPECT_STREQ(greedyStr, algorithmPointer->getName().c_str());

    delete algorithmPointer;
    algorithmPointer = new Steepest(10);
    char steepestStr[] = "Steepest";
    EXPECT_STREQ(steepestStr, algorithmPointer->getName().c_str());

    delete algorithmPointer;
    algorithmPointer = new Random(10);
    char randomStr[] = "Random";
    EXPECT_STREQ(randomStr, algorithmPointer->getName().c_str());

    delete algorithmPointer;
}
