//
// Created by jwarmbier on 24/11/2020.
//

#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "algorithm/RandomWalk.h"
#include "QAP.h"
#include <vector>
#include <stdlib.h>

TEST(RandomWalk, getNameTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP* sample = new QAP(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    RandomWalk algorithm(sample->getProblemSize());
    char  algorithmName[] = "RandomWalk";
    EXPECT_STREQ(algorithmName, algorithm.getName().c_str());
}