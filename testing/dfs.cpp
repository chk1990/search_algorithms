/**
 * @file bfs.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "DepthFirstSearch2D.h"

int main(int argc, char* argv[]) {
    DepthFirstSearch2D<float> search("./data_environment/plan2.dat");
    search.setGoal(Point2D<float>(55.5, 40.5));
    search.findPath(Point2D<float>(10.5, 3.0));
    std::cout << search.numVisitedPoints() << std::endl;
    std::cout << search.finalCost() << std::endl;
    search.printGrid();

    return 0;
}