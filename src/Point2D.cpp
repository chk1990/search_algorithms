/**
 * @file Point2D.cpp
 * @author Christoph Kolhoff
 */

#include <iostream>

#include "Point2D.h"

/**
 * @brief Constructor for point in origin
 */
template<typename T>
Point2D<T>::Point2D() : x(0), y(0) {}

/**
 * @brief Constructor for point with given coordinates
 * @param[in] x x-coordinate
 * @param[in] y y-coordinate
 */
template<typename T>
Point2D<T>::Point2D(T x, T y) : x(x), y(y) {}

/**
 * @brief Gets the x coordinate
 */
template<typename T>
T Point2D<T>::getX() const
{
    return this->x;
}

/**
 * @brief Gets the y coordinate
 */
template<typename T>
T Point2D<T>::getY() const
{
    return this->y;
}

/**
 * @brief Sets the x-coordinate of the point
 */
template<typename T>
void Point2D<T>::setX(T x)
{
    this->x = x;
}

/**
 * @brief Sets the y-coordinate of the point
 */
template<typename T>
void Point2D<T>::setY(T y)
{
    this->y = y;
}

/**
 * @brief Print the coordinates to stdout
 */
template<typename T>
void Point2D<T>::printCoordinates() const
{
    std::cout << "(" << this->getX() << ", " << this->getY() << ")";
}

/**
 * @brief Check if two points are equal
 * @param[in] pt Point to compare this one to
 */
template<typename T>
bool Point2D<T>::operator==(const Point2D<T>& pt) const {
    bool xComp = this->getX() == pt.getX();
    bool yComp = this->getY() == pt.getY();

    return xComp && yComp;
}