#include<iostream>

#include "GeneratePlan.h"

int main(int argc, char* argv[]) {

    GeneratePlan genPlan;
    genPlan.printPlan2D(1, "./data_environment/plan1.dat");

    return 0;
}