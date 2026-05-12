/**
 * @file Point2D.cpp
 * @author Christoph Kolhoff
 */

#include "Point2D.h"

Point2D::Point2D() : x(0), y(0) {}

Point2D::Point2D(int x, int y) : x(x), y(y) {}

/**
 * @brief Gets the x coordinate
 */
int Point2D::getX() const
{
    return this->x;
}

/**
 * @brief Gets the y coordinate
 */
int Point2D::getY() const
{
    return this->y;
}

/**
 * @brief Sets the x-coordinate of the point
 */
void Point2D::setX(int x)
{
    this->x = x;
}

/**
 * @brief Sets the y-coordinate of the point
 */
void Point2D::setY(int y)
{
    this->y = y;
}