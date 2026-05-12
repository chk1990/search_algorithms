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
        int x; /**< x-coordinates of the map */
        int y; /**< y-coordinates of the map */

    public:
        Point2D();
        Point2D(int x, int y);
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
};

#endif // H_POINT_2D_H