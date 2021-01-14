import os
import numpy as np
import matplotlib
from scipy.stats import pearsonr

import matplotlib.pyplot as plt


resultsDir = os.getcwd() + "/results"
figuresDir = resultsDir + "/figures"
optimalSolutions = {'chr25a': 3796,
                    'nug25': 3744,
                    'nug27': 5234,
                    'bur26a': 5426670}

timestamp = 10.0

figuresNum = [111, 112, 211, 221]

def getResults(datasetPath):
    algorithmResultsFiles = os.listdir(datasetPath)
    return algorithmResultsFiles

def getDatasetPath(datasetName):
    return resultsDir + "/" + datasetName

def readResults(file):
    lines = []
    file = open(file, 'r')
    lines = file.readlines()

    results = [line.split('\n')[0] for line in lines]
    results = np.asarray(results, dtype=np.float64)

    return results

def analyzeResults(pathDirectory):
    dataAnalysis = {}

    dataAnalysis['algorithmName'] = pathDirectory.split('/')[-1]
    dataAnalysis['datasetName'] = pathDirectory.split('/')[-2]
    dataAnalysis['optimalSolution'] = optimalSolutions[dataAnalysis['datasetName']]
    dataAnalysis['resultsPath'] = pathDirectory
    dataAnalysis['results'] = readResults(pathDirectory)
    dataAnalysis['resultsRelative'] = (dataAnalysis['results'] - dataAnalysis['optimalSolution'])/dataAnalysis['optimalSolution']
    dataAnalysis['std'] = np.std(dataAnalysis['results'])
    dataAnalysis['stdNormalize'] =  np.std((dataAnalysis['results']-dataAnalysis['optimalSolution'])/dataAnalysis['optimalSolution'])
    dataAnalysis['mean'] = np.mean(dataAnalysis['results'])
    dataAnalysis['max'] = np.max(dataAnalysis['results'])
    dataAnalysis['min'] = np.min(dataAnalysis['results'])
    dataAnalysis['meanTime'] = timestamp/len(dataAnalysis['results'])
    dataAnalysis['time'] = np.arange(0, timestamp, step=timestamp/len(dataAnalysis['results']))
    dataAnalysis['timeStep'] = timestamp/len(dataAnalysis['results'])
    return dataAnalysis

def rotateXtics(fig, value=15):
    for ax in fig.axes:
        plt.sca(ax)
        plt.xticks(rotation=value)

def minimumValuesGraph(datasets):
    figureType = "minValues"
    fig, axs = plt.subplots(2,2)


    for i in range(len(figuresNum)):
        fig = plt.figure()
        ax = fig.add_subplot(111)

        y =[]
        for result in datasets[i]:
            y.append((result['min'] - result['optimalSolution'])/ result['optimalSolution'])
        rects = ax.bar([result['algorithmName'] for result in datasets[i]], y)
        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)

        rotateXtics(fig, value=15)

        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        ax.set(ylabel="Wskaźnik efektywności")

        rotateXtics(fig, value=15)

        for rect in rects:
            height = np.round(rect.get_height(), 3)
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')
        fig.savefig(figuresDir + "/" + figureType +"_"+ str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()

def maximumValuesGraph(datasets):
    figureType = "maxValues"

    for i in range(len(figuresNum)):
        fig = plt.figure()
        ax = fig.add_subplot(111)

        y =[]
        for result in datasets[i]:
            y.append((result['max'] - result['optimalSolution'])/ result['optimalSolution'])
        ax.bar([result['algorithmName'] for result in datasets[i]], y)
        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        rotateXtics(fig, value=15)
        fig.savefig(figuresDir + "/" + figureType +"_"+ str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()

def meanValuesGraph(datasets):
    figureType = "meanValues"

    for i in range(len(figuresNum)):
        fig = plt.figure()
        ax = fig.add_subplot(111)

        y =[]
        for result in datasets[i]:
            y.append((result['mean'] - result['optimalSolution'])/ result['optimalSolution'])
        ax.bar([result['algorithmName'] for result in datasets[i]], y,
                               yerr=[result['stdNormalize'] for result in datasets[i]])
        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        rotateXtics(fig, value=15)
        fig.savefig(figuresDir + "/" + figureType +"_"+ str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()

def meanTimeGraph(datasets):
    figureType = "algorithmMeanTime"

    for i in range(len(figuresNum)):
        fig = plt.figure()
        ax = fig.add_subplot(111)

        y = []
        x = []
        for result in datasets[i]:
            y.append(result['meanTime'] * 1000)
            x.append(result['algorithmName'])

        rects = ax.bar(x, y)
        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        ax.set(ylabel="Średni czas [ms]")

        rotateXtics(fig, value=15)

        for rect in rects:
            height = np.round(rect.get_height(),3)
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

        fig.savefig(figuresDir + "/" + figureType + "_" + str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()

def efficiencyGraph(datasets):

    figureType = "efficiency"
    for i in range(len(figuresNum)):

        fig = plt.figure()
        ax = fig.add_subplot(111)

        y = []
        x = []

        for result in datasets[i]:
            efficiencyRate = 0.0

            x.append(result['algorithmName'])

            for j in range(len(result['resultsRelative'])-1):

                efficiencyRate = efficiencyRate + (result['resultsRelative'][j] + result['resultsRelative'][j+1])/2*(result['timeStep'])

            efficiencyRate = round(efficiencyRate, 3)
            y.append( efficiencyRate)

        rects = ax.bar(x, y)

        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        ax.set(ylabel="Wskaźnik efektywności")

        rotateXtics(fig, value=15)

        for rect in rects:
            height = np.round(rect.get_height(),3)
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

        fig.savefig(figuresDir + "/" + figureType + "_" + str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()

def meanSteps(datasets):
    figureType = "meanStepsValue"

    for i in range(len(figuresNum)):
        fig = plt.figure()
        ax = fig.add_subplot(111)

        y = []
        x = []
        for result in datasets[i]:
            if(result["algorithmName"] == "Greedy" or result["algorithmName"] == "Steepest"):
                y.append(len(result['results']))
                x.append(result['algorithmName'])

        rects = ax.bar(x, y)
        ax.set_title(str(datasets[i][0]['datasetName']), pad=15)
        ax.set(ylabel="Średnia liczba kroków")

        rotateXtics(fig, value=15)

        for rect in rects:
            height = np.round(rect.get_height(),3)
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

        fig.savefig(figuresDir + "/" + figureType + "_" + str(datasets[i][0]['datasetName']) + ".eps", format="eps")
        fig.show()
def browsedSolutions():
    figureType = "browsedSolutions"

    datasetNames = os.listdir(resultsDir + "/browsedSolution")
    datasetResultsPath = resultsDir + "/browsedSolution"

    for datasetName in datasetNames:
        print(datasetName)
        fig = plt.figure()
        ax = fig.add_subplot(111)

        algorithmNames = getResults(datasetResultsPath + "/" + datasetName)

        print(algorithmNames)
        x = []
        y = []
        for algorithm in algorithmNames:
            x.append(algorithm)
            file = open(datasetResultsPath + "/" + datasetName + "/" + algorithm, 'r')
            lines = file.readlines()
            y.append(float(lines[0]))

        rects = ax.bar(x, y)
        ax.set_title(datasetName, pad=15)
        ax.set(ylabel="Średnia liczba kroków")

        rotateXtics(fig, value=15)

        for rect in rects:
            height = np.round(rect.get_height(),3)
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

        fig.savefig(figuresDir + "/" + figureType + "_" + datasetName + ".eps", format="eps")
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

if __name__ == "__main__":
    datasetNames = os.listdir(resultsDir)

    datasetNames.remove('figures')
    datasetNames.remove('browsedSolution')
    datasetNames.remove("beginningEnd")
    datasetNames.remove("ends")
    datasetNames.remove("quality")

    # read data from files

    datasets = []
    for datasetName in datasetNames:
        datasetResultsPath = getDatasetPath(datasetName)

        algorithmNames = getResults(datasetResultsPath)

        listOfResults = []
        for algorithm in algorithmNames:
            algorithmResultsPath = datasetResultsPath + "/" + algorithm
            listOfResults.append(analyzeResults(algorithmResultsPath))


        datasets.append(listOfResults)

    # qualityProximityComparison()
    # resetComparison()
    # beginningEndComparison()
    # browsedSolutions()
    minimumValuesGraph(datasets)
    # maximumValuesGraph(datasets)
    # meanValuesGraph(datasets)
    # meanTimeGraph(datasets)
    # meanSteps(datasets)

