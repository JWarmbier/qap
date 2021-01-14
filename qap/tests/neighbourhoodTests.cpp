//
// Created by jwarmbier on 17/11/2020.
//

#include <stdio.h>
#include <gtest/gtest.h>
#include "utils.h"
#include <string>
#include <vector>
#include "neighbourGenerator.h"

using namespace std;
using testing::Eq;

void comparingArrays(int *expected, const int *actual, int size){
    for(int i= 0 ; i < 0; i ++)
        EXPECT_EQ(expected[i], actual[i]);
}

TEST(neighbourGenerator, nextNeighbourTest)
{   int size = 6;
    int permutation[] = {1, 2, 3, 4, 5, 6};

    neighbourGenerator *generator = new neighbourGenerator(permutation, size);

    for(int i = 0; i < size; i++){
        for(int j = i +1; j < size; j++){
            EXPECT_EQ(true, generator->hasNext());
            swap(permutation[i], permutation[j]); // next neighbour
            comparingArrays(generator->Next(), permutation, size);
            swap(permutation[i], permutation[j]); // return back to original solution
        }
    }
    EXPECT_EQ(false, generator->hasNext());
}

TEST(neighbourGenerator, setPermutationTest){
    int size = 4;
    int *permutation = new int[size]{1, 2, 3, 4};

    neighbourGenerator *generator = new neighbourGenerator(permutation, size);
    comparingArrays(generator->getOrgPermutation(), permutation, size);

    delete[] permutation;
    size = 5;
    permutation = new int[size]{1, 2, 3, 4, 5};

    generator->setPermutation(permutation, size);
    comparingArrays(generator->getOrgPermutation(), permutation, size);
}
