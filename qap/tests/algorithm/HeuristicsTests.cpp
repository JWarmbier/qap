//
// Created by jwarmbier on 24/11/2020.
//

#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "algorithm/Greedy.h"
#include "QAP.h"
#include <vector>
#include <stdlib.h>
#include "algorithm/Heuristics.h"


TEST(Heuristics, getNameTest){
    string filename = "../instances/small/data/bur26a.dat";
    QAP* sample = new QAP(filename);

    if(!ifFileExists(filename)){
        cout << "Provide file to do tests: " << filename << endl;
        return;
    }

    Heuristics algorithm(sample->getProblemSize());
    char  algorithmName[] = "Heuristics";
    EXPECT_STREQ(algorithmName, algorithm.getName().c_str());

}