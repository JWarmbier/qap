//
// Created by jwarmbier on 21/11/2020.
//

#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "Steepest.h"
#include "QAP.h"
#include <vector>
#include <stdlib.h>

TEST(Steepest, getNameTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP* sample = new QAP(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    Steepest algorithm(sample->getProblemSize());
    char  algorithmName[] = "Steepest";
    EXPECT_STREQ(algorithmName, algorithm.getName().c_str());
}