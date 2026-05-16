/**
 * @file search_base.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "AStar2D.h"
#include "SearchBase2D.h"

int main(int argc, char* argv[]) {

    AStar2D<float> base("./data_environment/plan1.dat");

    base.print();

    return 0;
}