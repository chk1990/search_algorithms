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
template <typename T>
Grid2D<T>::Grid2D(const size_t width, const size_t height, const T step) : Grid2D(width, height, step, static_cast<T>(0), static_cast<T>(0)) {}

/**
 * @brief Initialize a map with given dimensions
 * @param[in] height Height of map
 * @param[in] width Width of map
 * @param[in] step Horizontal and vertical distance between two points
 * @param[in] offX Offset in x-direction
 * @param[in] offY Offset in y-direction
 */
template <typename T>
Grid2D<T>::Grid2D(const size_t width, const size_t height, const T step,
                  const T offX, const T offY) : width(width),
                                                height(height),
                                                step(step),
                                                coordinates(std::make_unique<Point2D<T>[]>(height * width)),
                                                occupancy(std::make_unique<Occupancy[]>(height * width)),
                                                discovered(std::make_unique<bool[]>(height * width))
{
    // initialize map content with "nothing"
    std::fill(this->occupancy.get(), this->occupancy.get() + height * width, Occupancy::FREE);

    // populate map points with dimensions
    Point2D<T> *points = this->coordinates.get();

    for(size_t indY = 0; indY < height; ++indY) {
        for(size_t indX = 0; indX < width; ++indX) {
            size_t pos = index(indX, indY);

            T xVal = indX * step + offX;
            T yVal = indY * step + offY;

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
template <typename T>
size_t Grid2D<T>::index(const size_t col, const size_t row) const
{
    return row*width + col;
}

/**
 * @brief Get the height of the grid
 */
template <typename T>
size_t Grid2D<T>::getHeight() const
{
    return this->height;
}

/**
 * @brief Get the width of the grid
 */
template <typename T>
size_t Grid2D<T>::getWidth() const
{
    return this->width;
}

/**
 * @brief Get the step size of the grid
 */
template <typename T>
T Grid2D<T>::getStep() const
{
    return this->step;
}

/**
 * @brief Returns the point at the given location
 * @param[in] row Row index of interest
 * @param[in] col Column index of interest
 */
template <typename T>
Point2D<T> Grid2D<T>::getCoordinates(const size_t col, const size_t row) const
{
    size_t c = col;
    if(col >= width) {
        c = width - 1;
    }
    else if(col < 0) {
        c = 0;
    }

    size_t r = row;
    if(row >= height) {
        r = height - 1;
    }
    else if(row < 0) {
        r = 0;
    }

    size_t ind = index(c, r);
    Point2D<T> pt = *(this->coordinates.get() + ind);

    return pt;
}

/**
 * @brief Print the map's content to stdout
 */
template <typename T>
void Grid2D<T>::printContent() const
{
    // upper border line
    for(size_t indX = 0; indX <= width + 1; ++indX) {
        std::cout << "#";

        if(indX <= width) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }

    Occupancy *occ = occupancy.get();
    for(size_t indY = 0; indY < height; ++indY) {
        for(size_t indX = 0; indX < width; ++indX) {

            size_t ind = index(indX, indY);

            if(indX == 0) {
                // left limit
                std::cout << "# ";
            }

            switch (occ[ind]) {
                case Occupancy::FREE:
                    std::cout << " ";
                    break;

                case Occupancy::OBSTACLE:
                std::cout << "X";
                break;
            
                default:
                    break;
            }

            if(indX == width - 1) {
                // right limit
                std::cout << " #" << std::endl;
            } else {
                std::cout << " ";
            }
        }
    }

    // lower border line
    for(size_t indX = 0; indX <= width + 1; ++indX) {
        std::cout << "#";

        if(indX <= width) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }
}

/**
 * @brief Print the map's coordinates to stdout
 */
template <typename T>
void Grid2D<T>::printCoordinates() const
{
    Point2D<T> *points = coordinates.get();
    for(size_t indY = 0; indY < height; ++indY) {
        for(size_t indX = 0; indX < width; ++indX) {
            size_t ind = index(indX, indY);
            points[ind].printCoordinates();

            if(indX == width - 1) {
                std::cout << std::endl;
            } else {
                std::cout << " ";
            }
        }
    }
}

/**
 * @brief Set a point of the map as unknown in occupancy
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setFree(const size_t col, const size_t row)
{
    Occupancy* occ =  occupancy.get();
    size_t ind = index(col, row);
    occ[ind] = Occupancy::FREE;
}

/**
 * @brief Set a point of the map as unknown in occupancy
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setObstacle(const size_t col, const size_t row)
{
    Occupancy* occ =  occupancy.get();
    size_t ind = index(col, row);
    occ[ind] = Occupancy::OBSTACLE;
}

/**
 * @brief Returns if the point if free
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isFree(const size_t col, const size_t row) const
{
    return occupancy.get()[index(col, row)] == Occupancy::FREE;
}

/**
 * @brief Returns if the point if free
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isObstacle(const size_t col, const size_t row) const
{
    return occupancy.get()[index(col, row)] == Occupancy::OBSTACLE;
}

/**
 * @brief Sets the state of the point as discovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setDiscovered(const size_t col, const size_t row)
{
    discovered.get()[index(col, row)] = true;
}

/**
 * @brief Sets the state of the point as undiscovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setUndiscovered(const size_t col, const size_t row)
{
    discovered.get()[index(col, row)] = false;
}

/**
 * @brief Checks if the point is discovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isDiscovered(const size_t col, const size_t row) const
{
    return discovered.get()[index(col, row)];
}