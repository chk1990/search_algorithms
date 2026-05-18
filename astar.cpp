/**
 * @file search_base.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "AStar2D.h"

int main(int argc, char* argv[]) {

    AStar2D<float> search("./data_environment/plan1.dat");
    search.findPath(Point2D<float>(1.0, 1.0), Point2D<float>(27.0, 17.0));

    return 0;
}