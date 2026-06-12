/**
 * @file astar.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "AStar2D.h"

int main(int argc, char* argv[]) {
    /*
    AStar2D<float> search("./data_environment/plan1.dat");
    search.setGoal(Point2D<float>(42.0, 27.0));
    search.findPath(Point2D<float>(1.5, 1.5));
    */

    AStar2D<float> search("./data_environment/plan2.dat");
    search.setGoal(Point2D<float>(55.5, 40.5));
    search.findPath(Point2D<float>(10.5, 3.0));
    
    search.printGrid();

    return 0;
}