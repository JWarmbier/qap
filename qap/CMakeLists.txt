cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
#set the project name
project(qap)

#add the executable
add_executable(qap main.cpp includes/utils.cpp includes/utils.h includes/QAP.cpp includes/QAP.h tests/testUtils.cpp includes/QAPException.h tests/QAPTests.cpp includes/AlgorithmStrategy.cpp includes/AlgorithmStrategy.h includes/neighbourGenerator.cpp includes/neighbourGenerator.h tests/neighbourhoodTests.cpp tests/Algorithms/AlgorithmStrategyTests.cpp includes/Steepest.cpp includes/Steepest.h includes/Greedy.cpp includes/Greedy.h includes/Random.cpp includes/Random.h tests/Algorithms/SteepestTests.cpp tests/Algorithms/GreedyTests.cpp tests/Algorithms/RandomTests.cpp tests/include/utilsForTests.cpp tests/include/utilsForTests.h includes/Heuristics.cpp includes/Heuristics.h tests/Algorithms/HeuristicsTests.cpp includes/RandomWalk.cpp includes/RandomWalk.h tests/Algorithms/RandomWalkTests.cpp)

#add the test executable



include_directories(includes)
include_directories(tests/include)

#Google Test initialization
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(qap gtest gtest_main)



