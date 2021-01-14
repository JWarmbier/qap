//
// Created by jwarmbier on 28/10/2020.
//

#include "QAP.h"

QAP::QAP(string pathToData, string pathToSolution) {
    this->pathToData = pathToData;
    this->pathToSolution = pathToSolution;
    this->problemSize = -1;
    this->hasAlgorithmFinished = false;
    getProblemSizeFromFile();

    this->algorithm = NULL;

    if(this->problemSize == -1)
        throw QAPDataFileError();

    this->flows = new unsigned long long [this->problemSize*this->problemSize];
    this->distances = new unsigned long long [this->problemSize*this->problemSize];

    this->optimalSolution = new int [this->problemSize];
    this->solution = NULL;

    loadData();

    try{ // loading solution
        if(this->pathToSolution != "")
            this->loadSolutionFromFile(this->pathToSolution);
    } catch (exception e){
        cout << e.what() << endl;
    }
}

QAP::~QAP() {
    if(flows != NULL)
        delete[] flows;
    if(distances != NULL)
        delete[] distances;
    if(this->solution != NULL)
        delete[] this->solution;
    if(this->optimalSolution != NULL)
        delete[] this->optimalSolution;
}

void QAP::getProblemSizeFromFile() {
    ifstream file(this->pathToData);
    string line;

    while(getline(file, line)){
        vector<string> words = splitIntoWords(line);

        if(words.size() == 1 && this->problemSize == -1){
            this->problemSize = std::stoi(words[0].c_str());
            break;
        }
    }

    file.close();
}
void QAP::loadData() {
    ifstream file(this->pathToData);

    string inputBuffer;
    file >> inputBuffer;
    this->problemSize = stoi(inputBuffer.c_str());

    for(int i = 0; i < this->problemSize*this->problemSize; i ++){
        file >> inputBuffer;
        this->flows[i] = stoi(inputBuffer.c_str());
    }

    for(int i = 0; i < this-> problemSize* this->problemSize; i++){
        file >> inputBuffer;
        this->distances[i] = stoi(inputBuffer.c_str());
    }
}

void QAP::loadSolutionFromFile(string path) {
    this->pathToSolution = path;

    if(!ifFileExists(path))
        throw QAPSolutionError();

    ifstream file(this->pathToSolution);
    string line;

    string problemSize, solution;

    file >> problemSize >> solution; // read from file

    if(this->problemSize != stoi(problemSize))
        throw QAPSolutionError();

    this->optimalCost = stoi(solution);

    string number;
    for(int i = 0; i < this->problemSize; i++){
        file >> number;
        this->optimalSolution[i] = stol(number);
    }
}

unsigned long long int QAP::calculateCost(int *permutation) {
    unsigned long long int cost = 0;
    for(int i = 0; i < this->problemSize; i++){
        for(int j = 0; j < this->problemSize; j++){
            cost += this->distances[getElement(permutation[i]-1,permutation[j]-1)]* this->flows[getElement(i,j)];
        }
        cout << endl;
    }
    return cost;
}

int QAP::getElement(int row, int col) {
    return row*this->problemSize + col;
}

unsigned long long int * QAP::getDistances() {
    return this->distances;
}

unsigned long long int * QAP::getFlows() {
    return this->flows;
}

void QAP::setOptimalSolution(int *foundBestSolution) {
    this->solution = foundBestSolution;
}

int QAP::getProblemSize() {
    return this->problemSize;
}

void QAP::setAlgorithmStrategy(AlgorithmStrategy *algorithm) {
    this->algorithm = algorithm;
    this->solution = algorithm->getSolution();
}

string QAP::getAlgorithmName() {
    return this->algorithm->getName();
}

int *QAP::getOptimalSolution() {
    return this->optimalSolution;
}

int *QAP::getSolution() {
    return this->solution;
}

void QAP::algorithmStep() {

    this->solution = this->algorithm->step(this);
    this->cost = this->calculateCost(this->solution);
    this->hasAlgorithmFinished = this->algorithm->getHasFinished();

    if(this->hasAlgorithmFinished)
        this->algorithm->reset();
}

long QAP::getOptimalCost() {
    return this->optimalCost;
}

long QAP::getCost() {
    return this->cost;
}

bool QAP::getHasAlgorithmFinished() {
    return this->hasAlgorithmFinished;
}

void QAP::resetAlgorithm() {
    this->algorithm->reset();
    this->hasAlgorithmFinished = this->algorithm->getHasFinished();
}

float QAP::optimalSolutionSimilarity() {
    float counter = 0;
    for(int i = 0; i < this->problemSize; i++){
        if(optimalSolution[i] == solution[i])
            counter += 1;
    }
    return counter/this->problemSize;
}




