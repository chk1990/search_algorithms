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
Grid2D<T>::Grid2D(const size_t heigth, const size_t width, const T step) : Grid2D(heigth, width, step, 0, 0) {}

/**
 * @brief Initialize a map with given dimensions
 * @param[in] heigth Heigth of map
 * @param[in] width Width of map
 * @param[in] step Horizontal and vertical distance between two points
 * @param[in] offX Offset in x-direction
 * @param[in] offY Offset in y-direction
 */
template<typename T>
Grid2D<T>::Grid2D(const size_t heigth, const size_t width, const T step,
                  const T offX, const T offY) : heigth(heigth),
                                                width(width),
                                                step(step),
                                                coordinates(std::make_unique<Point2D<T>[]>(heigth*width)),
                                                occupancy(std::make_unique<uint8_t[]>(heigth*width))
{
    // initialize map content with "nothing"
    std::fill(this->occupancy.get(), this->occupancy.get() + heigth*width, 0);

    // populate map points with dimensions
    for(size_t indY = 0; indY < heigth; ++indY) {
        for(size_t indX = 0; indX < width; ++indX) {
            size_t pos = index(indX, indY);
            (this->coordinates.get() + pos)->setX(indX * step + offX);
            (this->coordinates.get() + pos)->setY(indY * step + offY);
        }
    }
}

/**
 * @brief Determine the index in the arrays corresponding to the row and column
 * @param[in] row Row index of interest, starting at 0
 * @param[in] col Column index of interest, starting at 0
 * @return Index in member array
 */
template<typename T>
size_t Grid2D<T>::index(const size_t col, const size_t row) const
{
    return row*(this->width) + col;
}

/**
 * @brief Get the heigth of the grid
 */
template<typename T>
size_t Grid2D<T>::getHeigt() const
{
    return this->heigth;
}

/**
 * @brief Get the width of the grid
 */
template<typename T>
size_t Grid2D<T>::getWidth() const
{
    return this->width;
}

template class Grid2D<int>;
template class Grid2D<float>;
template class Grid2D<double>;