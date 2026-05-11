/**
 * @file GeneratePlan.cpp
 * @author Christoph Kolhoff
 */

#include "GeneratePlan.h"

GeneratePlan::GeneratePlan() {}

/**
 * @brief Specifies a plan index, generates it and stores it
 * @param[in] ind Index of plan
 * @param[in] fileName Name of the file to store the plan in
 */
void GeneratePlan::printPlan(const size_t ind, const std::string fileName) const
{
    switch (ind) {
    case 1:
        printPlan1(fileName);
        break;
    
    default:
        break;
    }
}

/**
 * @brief Generates plan with index 1 and stores it in file
 * @param[in] fileName Name of the file to store the plan in
 */
void GeneratePlan::printPlan1(const std::string fileName) const
{
    std::cout << fileName << std::endl;
}