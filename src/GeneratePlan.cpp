/**
 * @file GeneratePlan.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include "GeneratePlan.h"

template<typename T>
GeneratePlan<T>::GeneratePlan() {}

/**
 * @brief Specifies a 2D plan index, generates it and stores it
 * @param[in] ind Index of plan
 * @param[in] filename Name of the file to store the plan in
 */
template<typename T>
void GeneratePlan<T>::genPlan2D(const size_t ind, const std::string filename)
{
    switch (ind) {
    case 1:
        genPlan2D1(filename);
        break;
    
    case 2:
        genPlan2D2(filename);
        break;

    default:
        break;
    }
}

/**
 * @brief Generates 2D plan with index 1 and stores it in file
 * @param[in] filename Name of the file to store the plan in
 */
template<typename T>
void GeneratePlan<T>::genPlan2D1(const std::string filename)
{
    const size_t width = 30;
    const size_t height = 20;
    Grid2D<T> grid(width, height, 1.5);

    for(size_t indX = 0; indX <= 15; ++indX) {
        grid.setObstacle(indX, 3);
        grid.setObstacle(indX, 11);
    }

    for(size_t indX = 12; indX < width; ++indX) {
        grid.setObstacle(indX, 7);
        grid.setObstacle(indX, 15);
    }

    grid.printContent();
    grid.exportPlanFile(filename);
}

/**
 * @brief Generates 2D plan with index 1 and stores it in file
 * @param[in] filename Name of the file to store the plan in
 */
template<typename T>
void GeneratePlan<T>::genPlan2D2(const std::string filename)
{
    const size_t width = 40;
    const size_t height = 30;
    Grid2D<T> grid(width, height, 1.5);

    for(size_t indX = 0; indX <= 20; ++indX) {
        grid.setObstacle(indX, 5);
        grid.setObstacle(indX, 17);
    }

    for(size_t indX = 15; indX < width; ++indX) {
        grid.setObstacle(indX, 11);
        grid.setObstacle(indX, 23);
    }

    grid.printContent();
    grid.exportPlanFile(filename);
}