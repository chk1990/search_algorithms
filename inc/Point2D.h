/**
 * @file Point2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_POINT_2D_H
#define H_POINT_2D_H

/**
 * @class Point2D
 * @brief Represents a point with 2D coordinates
 * 
 *        The type T can be int, float, double.
 */
template<typename T>
class Point2D {
    private:
        T x; /**< x-coordinates of the map */
        T y; /**< y-coordinates of the map */

    public:
        Point2D();
        Point2D(T x, T y);
        T getX() const;
        T getY() const;
        void setX(T x);
        void setY(T y);
};

#endif // H_POINT_2D_H