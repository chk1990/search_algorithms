/**
 * @file Grid2D.cpp
 * @author Christoph Kolhoff
 */

#include <iostream>
#include <memory>

#include "Grid2D.h"

/**
 * @brief Initialize a map with given dimensions
 * @param[in] height Height of map
 * @param[in] width Width of map
 * @param[in] step Horizontal and vertical distance between two points
 */
template<typename T>
Grid2D<T>::Grid2D(const size_t height, const size_t width, const T step) : Grid2D(height, width, step, 0, 0) {}

/**
 * @brief Initialize a map with given dimensions
 * @param[in] height Height of map
 * @param[in] width Width of map
 * @param[in] step Horizontal and vertical distance between two points
 * @param[in] offX Offset in x-direction
 * @param[in] offY Offset in y-direction
 */
template<typename T>
Grid2D<T>::Grid2D(const size_t height, const size_t width, const T step,
                  const T offX, const T offY) : height(height),
                                                width(width),
                                                step(step),
                                                coordinates(std::make_unique<Point2D<T>[]>(height*width)),
                                                occupancy(std::make_unique<uint8_t[]>(height*width))
{
    // initialize map content with "nothing"
    std::fill(this->occupancy.get(), this->occupancy.get() + height*width, 0);

    // populate map points with dimensions
    Point2D<T>* points = this->coordinates.get();
    for(size_t indY = 0; indY < height; ++indY) {
        for(size_t indX = 0; indX < width; ++indX) {
            size_t pos = index(indX, indY);

            T xVal = indX*step + offX;
            T yVal = indY*step + offY;

            points[pos].setX(xVal);
            points[pos].setY(yVal);
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
 * @brief Get the height of the grid
 */
template<typename T>
size_t Grid2D<T>::getHeight() const
{
    return this->height;
}

/**
 * @brief Get the width of the grid
 */
template<typename T>
size_t Grid2D<T>::getWidth() const
{
    return this->width;
}

/**
 * @brief Get the step size of the grid
 */
template<typename T>
T Grid2D<T>::getStep() const
{
    return this->step;
}

/**
 * @brief Returns the point at the given location
 * @param[in] row Row index of interest
 * @param[in] col Column index of interest
 */
template<typename T>
Point2D<T> Grid2D<T>::getCoordinates(const size_t col, const size_t row) const
{
    size_t ind = index(col, row);
    std::cout << col << " " << row << " " << width << " " << height << " " << ind << std::endl;
    Point2D<T> pt = *(this->coordinates.get() + ind);
 
    return pt;
}

template class Grid2D<int>;
template class Grid2D<float>;
template class Grid2D<double>;