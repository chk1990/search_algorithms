/**
 * @file Grid2D.cpp
 * @author Christoph Kolhoff
 */

#include <memory>

#include "Grid2D.h"

/**
 * @brief Initialize a map with given dimensions
 * @param[in] heigth Heigth of map
 * @param[in] width Width of map
 */
Grid2D::Grid2D(size_t heigth, size_t width) : heigth(heigth),
                                               width(width),
                                               coordinates(std::make_unique<Point2D[]>(heigth*width))
{
    std::fill(this->occupancy.get(), this->occupancy.get() + heigth*width, 0); // to be replaced
}

/**
 * @brief Determine the index in the arrays corresponding to the row and column
 * @param[in] row Row index of interest, starting at 0
 * @param[in] col Column index of interest, starting at 0
 * @return Index in member array
 */
size_t Grid2D::index(const size_t row, const size_t col) const
{
    return row*this->width + col;
}