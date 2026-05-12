/**
 * @file Grid2D.cpp
 * @author Christoph Kolhoff
 */

#include <iostream>
#include <memory>

#include "Grid2D.h"

/**
 * @brief Initialize a map with given dimensions
 * @param[in] heigth Heigth of map
 * @param[in] width Width of map
 * @param[in] step Horizontal and vertical distance between two points
 */
template<typename T>
Grid2D<T>::Grid2D(size_t heigth, size_t width, T step) : heigth(heigth),
                                               width(width),
                                               step(step),
                                               coordinates(std::make_unique<Point2D<T>[]>(heigth*width)),
                                               occupancy(std::make_unique<uint8_t[]>(heigth*width))
{
    //std::cout << "Constructor Grid2D" << std::endl;

    // initialize map content with "nothing"
    std::fill(this->occupancy.get(), this->occupancy.get() + heigth*width, 0); // to be replaced

    // populate map points with dimensions
}

/**
 * @brief Determine the index in the arrays corresponding to the row and column
 * @param[in] row Row index of interest, starting at 0
 * @param[in] col Column index of interest, starting at 0
 * @return Index in member array
 */
template<typename T>
size_t Grid2D<T>::index(const size_t row, const size_t col) const
{
    return row*this->width + col;
}

template class Grid2D<int>;
template class Grid2D<float>;
template class Grid2D<double>;