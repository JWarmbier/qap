//
// Created by jwarmbier on 04/11/2020.
//
#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "utils.h"
#include <string>
#include <vector>
#include "utilsForTests.h"

using namespace std;
using testing::Eq;

TEST(utils, ifEnoughArgumentsFalseReturn){
    EXPECT_FALSE(ifEnoughArguments(-1));
    EXPECT_FALSE(ifEnoughArguments(0));
    EXPECT_FALSE(ifEnoughArguments(1));
}

TEST(utils, ifEnoughArgumentsTrueReturn){
    EXPECT_TRUE(ifEnoughArguments(2));
    EXPECT_TRUE(ifEnoughArguments(10));
}

TEST(utils, ifFileExistsIfFalse){
    EXPECT_FALSE(ifFileExists("file-which-does-not-exist.none"));
}

TEST(utils , ifFileExistsIfTrue){
    char fileName[] = "filename.txt";
    ofstream MyFile(fileName); // creating File
    MyFile.close();

    EXPECT_TRUE(ifFileExists("filename.txt"));

    remove(fileName);
}

TEST(utils, splitLineTest){
    string words[5] = {"To", "jest", "tekst", "z", "wyrazami."};
    string line;
    for(int i = 0; i < 5; i++) // create line
        line += words[i] + " ";

    vector<string> splitLine = splitIntoWords(line);

    EXPECT_EQ(5, splitLine.size());
    for(int i = 0; i < words->size(); i++){
        EXPECT_STREQ(words[i].c_str(), splitLine[i].c_str());
    }
}


TEST(utils, randomPermutationGeneratorTest){
    int size = 1;

    int * random = randomPermutationGenerator(size);
    assertUniqueAscending(random, size);
    delete [] random;

    size = 0;
    random = randomPermutationGenerator(size);
    assertUniqueAscending(random, size);
    delete [] random;

    size = 100;
    random = randomPermutationGenerator(size);
    assertUniqueAscending(random, size);
    delete [] random;
}
