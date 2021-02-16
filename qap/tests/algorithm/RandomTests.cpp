//
// Created by jwarmbier on 21/11/2020.
//

#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "algorithm/Random.h"
#include "QAP.h"
#include <vector>
#include <stdlib.h>

TEST(Random, getNameTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP* sample = new QAP(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    Random algorithm(sample->getProblemSize());
    char  algorithmName[] = "Random";
    EXPECT_STREQ(algorithmName, algorithm.getName().c_str());
}