cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
#set the project name
project(qap)

#add the executable
add_executable(qap main.cpp includes/utils.cpp includes/utils.h includes/QAP.cpp includes/QAP.h tests/testUtils.cpp includes/QAPException.h tests/QAPTests.cpp includes/algorithm/AlgorithmStrategy.cpp includes/algorithm/AlgorithmStrategy.h includes/neighbourGenerator.cpp includes/neighbourGenerator.h tests/neighbourhoodTests.cpp tests/algorithm/AlgorithmStrategyTests.cpp includes/algorithm/Steepest.cpp includes/algorithm/Steepest.h includes/algorithm/Greedy.cpp includes/algorithm/Greedy.h includes/algorithm/Random.cpp includes/algorithm/Random.h tests/algorithm/SteepestTests.cpp tests/algorithm/GreedyTests.cpp tests/algorithm/RandomTests.cpp tests/include/utilsForTests.cpp tests/include/utilsForTests.h includes/algorithm/Heuristics.cpp includes/algorithm/Heuristics.h tests/algorithm/HeuristicsTests.cpp includes/algorithm/RandomWalk.cpp includes/algorithm/RandomWalk.h tests/algorithm/RandomWalkTests.cpp)

#add the test executable



include_directories(includes)
include_directories(tests/include)

#Google Test initialization
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(qap gtest gtest_main)



