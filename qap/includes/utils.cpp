//
// Created by jwarmbier on 28/10/2020.
//

#include "utils.h"

bool ifEnoughArguments(int argc){
    if(argc < 2){
        return false;
    }

    return true;
}

string getPath(int argc, char **argv){
    if (ifEnoughArguments(argc)) {
        cout << "Input file: " << argv[1] << endl;
        string path(argv[1]);
        return path;
    }

    return "";
}

bool ifFileExists(string filePath) {
    ifstream file(filePath.c_str());
    return file.good();
}

vector<string> splitIntoWords(string line) {
    vector<string> words;

    for(int i = 0; i < line.length(); i++){
        string tmp ;
        while(isspace(line[i]) && i < line.length()) i++; // skip whitespaces

        while(!isspace(line[i]) && i < line.length()) { // rewrite word to tmp
            tmp += line[i];
            i++;
        }

        if (tmp.length() > 0)
            words.push_back(tmp);
    }

    return  words;
}

int *randomPermutationGenerator(int size) {
    int * permutation = new int[size];

    for(int i = 1; i <= size; i++) // fill array with ascending order with 1 to n
        permutation[i-1] = i;

    for(int i = 0; i < size; i++){
        int num = (rand() % ( size - i) + i);
        swap(permutation[i], permutation[num]);
    }
    return permutation;
}

void runQAPSolver(void (*task)(), double durationSec) {
    using namespace chrono;

    int counter = 0;
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    high_resolution_clock::time_point endTime;

    do{
        task();
        counter++;
        endTime = high_resolution_clock::now();
    } while (duration_cast<duration<double>>(endTime - startTime).count() < durationSec);
    cout << "Czas trwania: " << duration_cast<duration<double>>(endTime - startTime).count() << " sec" << endl;
}
