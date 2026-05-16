/**
 * @file SearchBase2D.cpp
 * @author Christoph Kolhoff
 */

#include "SearchBase2D.h"

/**
 * @brief Initialize search environment
 * @param[in] filename Name of file that contains the plan
 */
template<typename T>
SearchBase2D<T>::SearchBase2D(const std::string filename)
{
    grid = std::make_unique<Grid2D<T>>();
    grid.get()->importPlanFile(filename);

    //grid.get()->printContent();
    //grid.get()->printCoordinates();
}