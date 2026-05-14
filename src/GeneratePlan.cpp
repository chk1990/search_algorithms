/**
 * @file GeneratePlan.cpp
 * @author Christoph Kolhoff
 */

#include <iostream>

#include "GeneratePlan.h"
#include "Grid2D.h"

template<typename T>
GeneratePlan<T>::GeneratePlan() {}

/**
 * @brief Specifies a 2D plan index, generates it and stores it
 * @param[in] ind Index of plan
 * @param[in] fileName Name of the file to store the plan in
 */
template<typename T>
void GeneratePlan<T>::printPlan2D(const size_t ind, const std::string fileName) const
{
    switch (ind) {
    case 1:
        printPlan2D1(fileName);
        break;
    
    default:
        break;
    }
}

/**
 * @brief Generates 2D plan with index 1 and stores it in file
 * @param[in] fileName Name of the file to store the plan in
 */
template<typename T>
void GeneratePlan<T>::printPlan2D1(const std::string fileName) const
{
    size_t width = 10;
    size_t height = 5;
    Grid2D<T> grid(width, height, 1.0);

    //grid.printCoordinates();
    grid.printContent();
}

template class GeneratePlan<int>;
template class GeneratePlan<float>;
template class GeneratePlan<double>;