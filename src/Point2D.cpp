/**
 * @file Point2D.cpp
 * @author Christoph Kolhoff
 */

#include "Point2D.h"

Point2D::Point2D(unsigned int x, unsigned int y) : x(x), y(y) {}

/**
 * @brief Gets the x coordinate
 */
unsigned int Point2D::getX() const
{
    return this->x;
}

/**
 * @brief Gets the y coordinate
 */
unsigned int Point2D::getY() const
{
    return this->y;
}