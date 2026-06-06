/**
 * @file generate_plans.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "GeneratePlan.h"

int main(int argc, char* argv[]) {

    GeneratePlan<float> genPlan;
    genPlan.genPlan2D(1, "./data_environment/plan1.dat");
    genPlan.genPlan2D(2, "./data_environment/plan2.dat");

    Grid2D<float> grid;
    grid.importPlanFile("./data_environment/plan1.dat");

    return 0;
}