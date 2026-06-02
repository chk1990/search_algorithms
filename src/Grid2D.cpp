/**
 * @file Grid2D.cpp
 * @author Christoph Kolhoff
 */

#include<cstring>
#include<errno.h>
#include<fstream>
#include<iostream>
#include<limits.h>
#include<memory>

#include "Grid2D.h"

constexpr size_t LEN_CHARS_IN() {return 256;}

/**
 * @brief Initialize a map with default dimensions
 */
template <typename T>
Grid2D<T>::Grid2D() : Grid2D(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)) {}

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
    std::fill(this->occupancy.get(), this->occupancy.get() + this->height * this->width, Occupancy::FREE);
    std::fill(this->discovered.get(), this->discovered.get() + this->height * this->width, false);

    this->populatePoints(offX, offY);
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
    size_t ind = row*this->width + col;
    /*
    if(ind >= this->width*this->height) {
        errno = EINVAL;
        perror("Invalid inputs if Grid2D<T>::index() due to too high index result");
        exit(EXIT_FAILURE);
    }
    */

    return ind;
}

/**
 * @brief Marks the point as a goal
 * @param[in] ind Index of interest
 */
template <typename T>
void Grid2D<T>::setGoal(const size_t ind)
{
    this->occupancy.get()[ind] = Occupancy::GOAL;
}

/**
 * @brief Populate point coordinates of grid
 */
template <typename T>
void Grid2D<T>::populatePoints()
{
    this->populatePoints(static_cast<T>(0), static_cast<T>(0));
}

/**
 * @brief Populate point coordinates of grid with offset
 * @param[in] xOff Offset in x-direction
 * @param[in] yOff Offset in y-direction
 */
template <typename T>
void Grid2D<T>::populatePoints(const T xOff, const T yOff)
{
    Point2D<T> *points = this->coordinates.get();
    for(size_t indY = 0; indY < this->height; ++indY) {
        for(size_t indX = 0; indX < this->width; ++indX) {
            size_t pos = this->index(indX, indY);

            T xVal = indX * this->step + xOff;
            T yVal = indY * this->step + yOff;

            points[pos].setX(xVal);
            points[pos].setY(yVal);
        }
    }
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
 * @brief Determines the index of a point to find in the grid
 * @param[in] point Point to find in grid
 * @return Index of point
 */
template <typename T>
size_t Grid2D<T>::index(const Point2D<T>& point) const
{
    Point2D<T>* coors = this->coordinates.get();
    for(size_t ind = 0; ind < this->width*this->height; ++ind) {
        if(point.getX() == coors[ind].getX() && point.getY() == coors[ind].getY()) {
            return ind;
        }
    }

    return 0;
}

/**
 * @brief Returns the point at the given location
 * @param[in] row Row index of interest
 * @param[in] col Column index of interest
 */
template <typename T>
Point2D<T>& Grid2D<T>::getCoordinates(const size_t col, const size_t row) const
{
    size_t c = col;
    if(col >= this->width) {
        c = this->width - 1;
    }
    else if(col < 0) {
        c = 0;
    }

    size_t r = row;
    if(row >= this->height) {
        r = this->height - 1;
    }
    else if(row < 0) {
        r = 0;
    }

    size_t ind = index(c, r);
    Point2D<T>& pt = getCoordinates(ind);

    return pt;
}

/**
 * @brief Returns the point at the given location
 * @param[in] ind Index of interest
 */
template <typename T>
Point2D<T>& Grid2D<T>::getCoordinates(const size_t ind) const
{
    Point2D<T>& pt = *(this->coordinates.get() + ind);
    return pt;
}

/**
 * @brief Print the map's content to stdout
 */
template <typename T>
void Grid2D<T>::printContent() const
{
    // upper border line
    for(size_t indX = 0; indX <= this->width + 1; ++indX) {
        std::cout << "#";

        if(indX <= this->width) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }

    Occupancy* occ = this->occupancy.get();
    for(size_t indY = 0; indY < this->height; ++indY) {
        for(size_t indX = 0; indX < this->width; ++indX) {

            size_t ind = this->index(indX, indY);

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

                case Occupancy::PATH:
                    std::cout << "+";
                    break;
                case Occupancy::GOAL:
                    std::cout << "G";
                    break;

                default:
                    break;
            }

            if(indX == this->width - 1) {
                // right limit
                std::cout << " #" << std::endl;
            } else {
                std::cout << " ";
            }
        }
    }

    // lower border line
    for(size_t indX = 0; indX <= this->width + 1; ++indX) {
        std::cout << "#";

        if(indX <= this->width) {
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
    Point2D<T> *points = this->coordinates.get();
    for(size_t indY = 0; indY < this->height; ++indY) {
        for(size_t indX = 0; indX < this->width; ++indX) {
            size_t ind = this->index(indX, indY);
            points[ind].printCoordinates();

            if(indX == this->width - 1) {
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
    Occupancy* occ =  this->occupancy.get();
    size_t ind = this->index(col, row);
    occ[ind] = Occupancy::FREE;
}

/**
 * @brief Set a point of the map as unknown in occupancy
 * @param[in] ind Index of interest
 */
template <typename T>
void Grid2D<T>::setObstacle(const size_t ind)
{
    Occupancy* occ =  this->occupancy.get();
    occ[ind] = Occupancy::OBSTACLE;
}

/**
 * @brief Set a point of the map as unknown in occupancy
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setObstacle(const size_t col, const size_t row)
{
    Occupancy* occ =  this->occupancy.get();
    size_t ind = this->index(col, row);
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
    return this->occupancy.get()[this->index(col, row)] == Occupancy::FREE;
}

/**
 * @brief Returns if the point is an obstacle
 * @param[in] ind Index of interest
 */
template <typename T>
bool Grid2D<T>::isObstacle(const size_t ind) const
{
    return this->occupancy.get()[ind] == Occupancy::OBSTACLE;
}

/**
 * @brief Returns if the point is an obstacle
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isObstacle(const size_t col, const size_t row) const
{
    return this->occupancy.get()[this->index(col, row)] == Occupancy::OBSTACLE;
}

/**
 * @brief Sets the state of the point as part of the path
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setPath(const size_t col, const size_t row)
{
    size_t ind = this->index(col, row);
    this->setPath(ind);
}

/**
 * @brief Sets the state of the point as part of the path
 * @param[in] point Point to find in grid
 */
template <typename T>
void Grid2D<T>::setPath(const Point2D<T>& pt)
{
    size_t ind = this->index(pt);
    this->setPath(ind);
}

/**
 * @brief Returns if the point is part of the path
 * @param[in] ind Index of interest
 */
template <typename T>
bool Grid2D<T>::isPath(const size_t ind) const
{
    return this->occupancy.get()[ind] == Occupancy::PATH;
}

/**
 * @brief Returns if the point is part of the path
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isPath(const size_t col, const size_t row) const
{
    size_t ind = this->index(col, row);
    return this->isPath(ind);
}

/**
 * @brief Returns if the point is part of the path
 * @param[in] point Point to find in grid
 */
template <typename T>
bool Grid2D<T>::isPath(const Point2D<T>& pt) const
{
    size_t ind = this->index(pt);
    return this->isPath(ind);
}

/**
 * @brief Sets the state of the point as part of the path
 * @param[in] ind Index of interest
 */
template <typename T>
void Grid2D<T>::setPath(const size_t ind)
{
    Occupancy* occ = this->occupancy.get();
    occ[ind] = Occupancy::PATH;
    this->setDiscovered(ind);
}

/**
 * @brief Sets the state of the point as discovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setDiscovered(const size_t col, const size_t row)
{
    size_t ind = this->index(col, row);
    this->setDiscovered(ind);
}

/**
 * @brief Sets the state of the point as discovered
 * @param[in] ind Index of interest
 */
template <typename T>
void Grid2D<T>::setDiscovered(const size_t ind)
{
    this->discovered.get()[ind] = true;
}

/**
 * @brief Sets the state of the point as undiscovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void Grid2D<T>::setUndiscovered(const size_t col, const size_t row)
{
    this->discovered.get()[this->index(col, row)] = false;
}

/**
 * @brief Checks if the point is discovered
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
bool Grid2D<T>::isDiscovered(const size_t col, const size_t row) const
{
    size_t ind = this->index(col, row);
    return this->isDiscovered(ind);
}

/**
 * @brief Checks if the point is discovered
 * @param[in] ind Index of interest
 */
template <typename T>
bool Grid2D<T>::isDiscovered(const size_t ind) const
{
    return this->discovered.get()[ind];
}

/**
 * @brief Exports the plan to a file
 * @param[in] filename Name of the file
 * 
 * The exported file contains data as follows:\n
 * Line 1: Width of the map\n
 * Line 2: Height of the map\n
 * Line 3: Content of the map (free, obstancles, ...)\n
 * Line 4: Discovery state\n
 */
template <typename T>
void Grid2D<T>::exportPlanFile(const std::string& filename) const
{
    std::ofstream fileStream;
    fileStream.open(filename);
    if(!fileStream.is_open()) {
        perror("Failed to open file");
        return;
    }

    fileStream << this->width << std::endl << this->height << std::endl << this->step << std::endl;

    const Occupancy* occ = this->occupancy.get();
    for(size_t indY = 0; indY < this->height; ++indY) {
        for(size_t indX = 0; indX < this->width; ++indX) {
            fileStream << occ[this->index(indX, indY)];
        }
    }
    fileStream << std::endl;

    const bool* dis = this->discovered.get();
    for(size_t indY = 0; indY < this->height; ++indY) {
        for(size_t indX = 0; indX < this->width; ++indX) {
            fileStream << dis[this->index(indX, indY)];
        }
    }

    fileStream.close();
}

/**
 * @brief Imports the plan from a file
 * @param[in] filename Name of the file
 */
template<typename T>
void Grid2D<T>::importPlanFile(const std::string& filename)
{
    std::ifstream is;
    is.open(filename);

    if(!is.is_open()) {
        perror("Failed to open file");
        return;
    }

    // determine width, height and step
    char c[LEN_CHARS_IN()];
    is.getline(c, LEN_CHARS_IN());
    this->width = std::stoi(c);

    is.getline(c, LEN_CHARS_IN());
    this->height = std::stoi(c);

    is.getline(c, LEN_CHARS_IN());
    this->step = std::stoi(c);

    // populate other arrays
    this->coordinates = std::make_unique<Point2D<T>[]>(this->height*this->width);
    this->occupancy = std::make_unique<Occupancy[]>(this->height*this->width);
    this->discovered = std::make_unique<bool[]>(this->height*this->width);

    Occupancy* occ = this->occupancy.get();
    for(size_t indArr = 0; indArr < this->width*this->height; ++indArr) {
        int i = is.get() - '0';
        occ[indArr] = static_cast<Occupancy>(i);
    }

    is.get(); // remove '\n'

    bool* dis = this->discovered.get();
    for(size_t indArr = 0; indArr < this->width*this->height; ++indArr) {
        int i = is.get() - '0';
        
        if(i == 1) {
            dis[indArr] = true;
        } else {
            dis[indArr] = false;
        }
    }

    is.close();

    this->populatePoints();
}