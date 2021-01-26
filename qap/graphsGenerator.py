import os
import numpy as np
import matplotlib
from scipy.stats import pearsonr

import matplotlib.pyplot as plt


resultsDir = os.getcwd() + "/results"
figuresDir = resultsDir + "/figures"
optimalSolutions = {'chr12a': 9552.,
                    'chr25a': 3796.,
                    'nug25': 3744.,
                    'bur26a': 5426670.,
                    'nug27': 5234.,
                    'tai50b': 458821517.,
                    'lipa50a': 62093.,
                    'lipa50b': 1210244.}

timestamp = 10.0

figuresNum = [111, 112, 211, 221]

class Results:
    def __init__(self, filePath):
        self.results = []
        self.params = {}
        self.datasetName = ""
        self.algorithmName = ""
        self.optimalSolution = 0

        self.readResults(filePath)
        self.findOptimalSolution()

    def readResults(self, filePath):
        self.algorithmName = filePath.split('/')[-1]
        self.datasetName = filePath.split('/')[-2]
        file = open(filePath, 'r')
        lines = file.readlines()

        for line in lines:

            if(line.find(":") >= 0):
                paramName, value = line.split(":")
                value = float(value)

                if not paramName in self.params:
                    self.params[paramName] = []

                self.params[paramName].append(value)
            else:
                self.results.append(line.split('\n')[0])

        self.results = np.asarray(self.results, dtype=np.float64)

    def findOptimalSolution(self):
        self.optimalSolution = optimalSolutions[self.datasetName]

    def getOptimalSolution(self):
        return self.optimalSolution

    def getMean(self):
        return np.mean(self.results)

    def getStd(self):
        tmpResults = self.results
        tmpResults = (np.asarray(tmpResults) - self.getOptimalSolution())/self.getOptimalSolution()*100

        return np.std(tmpResults)

    def getMin(self):
        return np.min(self.results)

    def getMax(self):
        return np.max(self.results)

    def getAlgorithmName(self):
        return self.algorithmName

    def getDatasetName(self):
        return self.datasetName

    def getResults(self):
        return self.results

    def getTime(self):
        while "time" in self.params: return self.params["time"]
        return -1

    def averageTimeDuration(self):
        while "time" in self.params: return self.params["time"][0]/len(self.results)
        return -1

    def getEfficiency(self):
        relativeResults = (self.results - self.getOptimalSolution())/self.getOptimalSolution()*100

        if(len(relativeResults) == 1):
            return relativeResults[0]/self.params['time'][0]

        efficiencyRate = 0.0
        for j in range(len(relativeResults)-1):
            efficiencyRate = efficiencyRate + (relativeResults[j] + relativeResults[j+1])/2*(self.params['time'][0]/len(self.results))

        efficiencyRate = round(efficiencyRate/self.params['time'][0], 3)
        return efficiencyRate

    def getMeanSteps(self):
        return np.mean(np.asarray(self.params["steps"], dtype=np.float64))

    def getStdSteps(self):
        return np.std(np.asarray(self.params["steps"], dtype=np.float64))

    def getBrowsedSolutions(self):
        while "browsedSolutions" in self.params: return self.params["browsedSolutions"][0]
        return -1


def getResults(datasetPath):
    algorithmResultsFiles = os.listdir(datasetPath)
    return algorithmResultsFiles

def getDatasetPath(datasetName):
    return resultsDir + "/" + datasetName

def rotateXtics(fig, value=15):
    for ax in fig.axes:
        plt.sca(ax)
        plt.xticks(rotation=value)

def getDatasetNames(data):
    names = []
    for dataset in data:
        names.append(dataset[0].getDatasetName())

    return names

def addBarValues(ax, rects):
    for rect in rects:
        height = np.round(rect.get_height(), 3)
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 5),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

    return ax

def drawBarGraph(x, y, datasetName, ylabel="Wskaźnik jakości", yerr=None):
    fig = plt.figure()
    ax = fig.add_subplot(111)

    rects = ax.bar(x, y, yerr=yerr)

    ax.set_title(str(datasetName), pad=15)

    rotateXtics(fig, value=15)

    ax.set(ylabel=ylabel)

    addBarValues(ax, rects)

    return fig, ax

def saveFig(fig, graphType, datasetName):
    fig.savefig(figuresDir + "/" + graphType +"-" + str(datasetName) + ".eps", format="eps")

def minimumValuesGraph(data):
    graphType = "minValues"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x = [algorithm.getAlgorithmName() for algorithm in dataset]
        y = np.asarray([(algorithm.getMin() - algorithm.getOptimalSolution())/algorithm.getOptimalSolution() for algorithm in dataset], dtype=np.float64)
        y = np.round(y, 5)*100

        fig, ax = drawBarGraph(x, y, datasetName)

        saveFig(fig, graphType, datasetName)
        fig.show()

def maximumValuesGraph(data):
    graphType = "maxValues"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x = [algorithm.getAlgorithmName() for algorithm in dataset]
        y = np.asarray([(algorithm.getMax() - algorithm.getOptimalSolution())/algorithm.getOptimalSolution() for algorithm in dataset], dtype=np.float64)
        y = np.round(y, 5)*100

        fig, ax = drawBarGraph(x, y, datasetName)

        saveFig(fig, graphType, datasetName)
        fig.show()

def meanValuesGraph(data):
    graphType = "meanValues"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x = []
        y = []
        yerr = []
        for algorithm in dataset: #excluding Heuristics Algorithm
            if algorithm.getAlgorithmName() != "Heuristics":
                x.append(algorithm.getAlgorithmName())
                y.append((algorithm.getMean() - algorithm.getOptimalSolution())/algorithm.getOptimalSolution())
                yerr.append(algorithm.getStd())

        yerr = np.asarray(yerr)
        y = np.asarray(y)
        y = np.round(y, 5)*100

        fig, ax = drawBarGraph(x, y, datasetName, yerr=yerr)

        saveFig(fig, graphType, datasetName)
        fig.show()

def meanTimeGraph(data):
    graphType = "meanTimeValues"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x = [ algorithm.getAlgorithmName() for algorithm in dataset]
        y = [ algorithm.averageTimeDuration() for algorithm in dataset]

        y = np.asarray(y) * 1000
        y = np.round(y, 5)

        fig, ax = drawBarGraph(x, y, datasetName, ylabel="Średni czas działania [ms]")

        saveFig(fig, graphType, datasetName)
        fig.show()

def efficiencyGraph(data):
    graphType = "efficiency"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x , y = [], []
        for algorithm in dataset:
            if algorithm.getAlgorithmName() != "Heuristics":
                x.append(algorithm.getAlgorithmName())
                y.append(algorithm.getEfficiency())

        y = np.asarray(y)
        y = np.round(y, 5)

        fig, ax = drawBarGraph(x, y, datasetName, ylabel="Efektywność")

        saveFig(fig, graphType, datasetName)
        fig.show()

def meanSteps(data):
    graphType = "meanSteps"

    includedAlgorithms = ["Greedy", "Steepest"]
    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x , y , yerr = [], [], []
        for algorithm in dataset:
            if algorithm.getAlgorithmName() in includedAlgorithms:
                x.append(algorithm.getAlgorithmName())
                y.append(algorithm.getMeanSteps())
                yerr.append(algorithm.getStdSteps())

        y = np.asarray(y)
        y = np.round(y, 5)

        fig, ax = drawBarGraph(x, y, datasetName, ylabel="Średnia liczba kroków", yerr=yerr)

        saveFig(fig, graphType, datasetName)
        fig.show()

def browsedSolutions(data):
    graphType = "browsedSolutions"

    for dataset in data:
        datasetName = dataset[0].getDatasetName()

        x, y = [], []
        for algorithm in dataset: #excluding Heuristics Algorithm
            if algorithm.getAlgorithmName() != "Heuristics":
                x.append(algorithm.getAlgorithmName())
                y.append((algorithm.getBrowsedSolutions()))


        y = np.asarray(y)
        y = np.round(y)

        fig, ax = drawBarGraph(x, y, datasetName)

        saveFig(fig, graphType, datasetName)
        fig.show()

def beginningEndComparison():
    figureType = "beginningEnd"

    datasetNames = os.listdir(resultsDir + "/beginningEnd")
    datasetResultsPath = resultsDir + "/beginningEnd"

    datasets = []

    for datasetName in datasetNames:
        fig = plt.figure()
        ax = fig.add_subplot(111)

        algorithmNames = getResults(datasetResultsPath + "/" + datasetName)

        dataset = []
        for algorithm in algorithmNames:
            dataAnalysis = {}

            dataAnalysis['algorithmName'] = algorithm
            dataAnalysis['beginnings'] = []
            dataAnalysis['ends'] = []

            file = open(datasetResultsPath + "/" + datasetName + "/" + algorithm, 'r')
            lines = file.readlines()

            for line in lines:
                beginning, end = line.split()

                dataAnalysis['beginnings'].append(float(beginning))
                dataAnalysis['ends'].append(float(end))

            dataset.append(dataAnalysis)

        for algorithm in dataset:
            ax.scatter(algorithm['beginnings'], algorithm['ends'], s=10, label= algorithm['algorithmName'] + ", corr= " + str(round(pearsonr(algorithm['beginnings'],  algorithm['ends'])[0],3)))
        ax.set_title(datasetName, pad=15)
        ax.set(ylabel="Rozwiązania końcowe", xlabel="Rozwiązania początowe")
        ax.legend()
        fig.savefig(figuresDir + "/" + figureType + "_" + datasetName + ".eps", format="eps")
        fig.show()

def resetComparison():
    figureType = "analysis"

    datasetNames = os.listdir(resultsDir + "/ends")
    datasetResultsPath = resultsDir + "/ends"

    datasets = []

    for datasetName in datasetNames:
        algorithmNames = getResults(datasetResultsPath + "/" + datasetName)

        dataset = []
        for algorithm in algorithmNames:
            fig = plt.figure()
            ax = fig.add_subplot(111)
            dataAnalysis = {}

            dataAnalysis['algorithmName'] = algorithm

            file = open(datasetResultsPath + "/" + datasetName + "/" + algorithm, 'r')
            lines = file.readlines()

            dataAnalysis['results'] = [float(line) for line in lines]
            dataAnalysis['x'] = np.arange(len(dataAnalysis['results']))
            dataAnalysis['min'] = []
            dataAnalysis['mean'] = []
            for i in range( len(dataAnalysis['results'])):
                dataAnalysis['min'].append(min(dataAnalysis['results'][:i+1]))
                dataAnalysis['mean'].append(np.mean(dataAnalysis['results'][:i+1]))

            dataset.append(dataAnalysis)
            ax.scatter(dataAnalysis['x'], dataAnalysis['results'], label="kolejne rozwiązania", alpha=0.5)
            ax.scatter(dataAnalysis['x'], dataAnalysis['min'], label="najlepsze rozwiązania", alpha=0.5)
            ax.scatter(dataAnalysis['x'], dataAnalysis['mean'], label="średnia", alpha=0.5)
            ax.set_title("Zbiór " +datasetName + ", algorytm " + algorithm, pad=15)
            ax.set(xlabel="Liczba restartów", ylabel="koszt rozwiązania")

            ax.legend()

            fig.savefig(figuresDir + "/" + figureType + "_" + datasetName + "_" + algorithm + ".eps", format="eps")
            fig.show()

def qualityProximityComparison():
    figureType = "qualityProximity"

    datasetNames = os.listdir(resultsDir + "/quality")
    datasetResultsPath = resultsDir + "/quality"

    datasets = []

    for datasetName in datasetNames:
        fig = plt.figure()
        ax = fig.add_subplot(111)

        algorithmNames = getResults(datasetResultsPath + "/" + datasetName)

        dataset = []
        for algorithm in algorithmNames:
            dataAnalysis = {}

            dataAnalysis['algorithmName'] = algorithm
            dataAnalysis['beginnings'] = []
            dataAnalysis['ends'] = []

            file = open(datasetResultsPath + "/" + datasetName + "/" + algorithm, 'r')
            lines = file.readlines()

            for line in lines:
                beginning, end = line.split()

                dataAnalysis['beginnings'].append(float(beginning))
                dataAnalysis['ends'].append(float(end))

            dataset.append(dataAnalysis)

        for algorithm in dataset:
            ax.scatter(algorithm['beginnings'], algorithm['ends'], s=10, label= algorithm['algorithmName'])
        ax.set_title(datasetName, pad=15)
        ax.set(ylabel="Bliskość rozwiązania", xlabel="Jakość rozwiązania")
        ax.legend()
        fig.savefig(figuresDir + "/" + figureType + "_" + datasetName + ".eps", format="eps")
        fig.show()

def getSteepestTime(data):

    for dataset in data:
        for algorithm in dataset:
            if(algorithm.getAlgorithmName() == "Steepest"):
                print(algorithm.getDatasetName(), "time duration: ", np.round(algorithm.getTime(), 3))


if __name__ == "__main__":
    datasetNames = os.listdir(resultsDir)

    while "figures" in datasetNames: datasetNames.remove('figures')
    while "browsedSolution" in datasetNames: datasetNames.remove('browsedSolution')
    while "beginningEnd" in datasetNames: datasetNames.remove("beginningEnd")
    while "ends" in datasetNames: datasetNames.remove("ends")
    while "quality" in datasetNames: datasetNames.remove("quality")

    # read data from files

    datasets = []
    for datasetName in datasetNames:
        datasetResultsPath = getDatasetPath(datasetName)

        algorithmNames = getResults(datasetResultsPath)

        listOfResults = []
        for algorithm in algorithmNames:
            algorithmResultsPath = datasetResultsPath + "/" + algorithm

            dataAlgResults = Results(algorithmResultsPath)

            listOfResults.append(dataAlgResults)

        datasets.append(listOfResults)

    # getSteepestTime(datasets)
    # minimumValuesGraph(datasets)
    # maximumValuesGraph(datasets)
    # meanValuesGraph(datasets)
    # meanTimeGraph(datasets)
    # efficiencyGraph(datasets)
    # meanSteps(datasets)
    browsedSolutions(datasets)

    # qualityProximityComparison()
    # resetComparison()
    # beginningEndComparison()




