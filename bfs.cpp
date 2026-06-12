/**
 * @file bfs.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "BreadthFirstSearch2D.h"

int main(int argc, char* argv[]) {
    BreadthFirstSearch2D<float> search("./data_environment/plan2.dat");
    search.setGoal(Point2D<float>(55.5, 40.5));
    search.findPath(Point2D<float>(10.5, 3.0));
    
    search.printGrid();

    return 0;
}