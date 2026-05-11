/**
 * @file Point2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_POINT_2D_H
#define H_POINT_2D_H

/**
 * @class Point2D
 * @brief Represents a point with 2D coordinates
 */
class Point2D {
    private:
        unsigned int x;
        unsigned int y;

    public:
        Point2D(unsigned int x, unsigned int y);
        unsigned int getX() const;
        unsigned int getY() const;
};

#endif // H_POINT_2D_H