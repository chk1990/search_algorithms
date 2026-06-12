##

import matplotlib.patches as patches
import matplotlib.pyplot as plt
import sys

if __name__ == "__main__":
    """!
    How to use: python visualization plan1

    Where plan1 is a arbitrary name for a plan generated into the subdirectory data_environment where also a path and a tree file is available.

    """

    jobName = sys.argv[1]
    algorithm = sys.argv[2]

    gridName = "./data_environment/" + jobName + ".dat"
    pathName = "./data_environment/" + jobName + "_" + algorithm + "_path.dat"
    treeName = "./data_environment/" + jobName + "_" + algorithm + "_tree.dat"

    gridFile = open(gridName, 'r')
    gridContent = gridFile.read().split('\n')
    gridFile.close()

    treeFile = open(treeName, 'r')
    treeContent = treeFile.read().split('\n')
    treeFile.close()

    pathFile = open(pathName, 'r')
    pathContent = pathFile.read().split('\n')
    pathFile.close()
    
    # dimensions of the grid
    xSteps = int(gridContent[0])
    ySteps = int(gridContent[1])
    xLim = (float(xSteps) - 1) * float(gridContent[2])
    yLim = (float(ySteps) - 1) * float(gridContent[2])
    step = float(gridContent[2])
    obstacles = gridContent[3]

    plt.figure()
    ax = plt.gca()
    ax.set_facecolor((0.5,0.5,0.5))
    ax.set_xlim(0, xLim)
    ax.set_ylim(0, yLim)
    ax.set_xlabel("x [unit]")
    ax.set_ylabel("y [unit]")

    # draw map
    for i in range(0, len(obstacles)):
        ptInd = int(obstacles[i])

        if 1 == ptInd:
            # center point of the rectange
            xInd = i % xSteps
            yInd = i // xSteps
            
            rect = patches.Rectangle((step*xInd - step/2, step*yInd - step/2), step, step, edgecolor='k', facecolor='k')
            ax.add_patch(rect)

    # draw tree
    for indTree in range(1, len(treeContent) - 1):
        lineData = treeContent[indTree]
        coordinates = lineData.split(",")

        xData = [float(coordinates[0]), float(coordinates[2])]
        yData = [float(coordinates[1]), float(coordinates[3])]

        if indTree == 1:
            ax.plot(xData, yData, color=(0, 0, 1), label="search tree")
        else:
            ax.plot(xData, yData, color=(0, 0, 1), label="_nolegend_")

    # draw path
    xPath = []
    yPath = []
    for indPath in range(0, len(pathContent) - 1):
        coordinates = pathContent[indPath].split(",")
        xPath.append(float(coordinates[0]))
        yPath.append(float(coordinates[1]))

    ax.plot(xPath, yPath, color=(1,0,0), label="found path")

    ax.plot(xPath[0], yPath[0], 'o', color=(1, 0, 0), label="Start")
    ax.plot(xPath[-1], yPath[-1], 'o', color=(0, 1, 0), label="Goal")

    plt.legend()
    plt.show()