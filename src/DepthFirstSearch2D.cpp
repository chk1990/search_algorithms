/**
 * @file DepthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#include<cmath>

#include "DepthFirstSearch2D.h"

/**
 * @brief Initializes the path finding object
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
DepthFirstSearch2D<T>::DepthFirstSearch2D(const std::string& filename) : SearchBase2D<T>(filename, "bfs"),
                                                                         stack(std::make_unique<std::stack<pathElement>>())
{
    //
}

/**
 * @brief Finds the path from start to goal if the path is available
 * @param[in] start Point to start
 * @param[in] goal Desired end of path
 * @todo complete and test
 */
template<typename T>
void DepthFirstSearch2D<T>::findPath(const Point2D<T>& start, const Point2D<T>& goal)
{
    //
}

/**
 * @brief Adds a point to the priority queue
 * @param[in] ind Index of point to add
 * @param[in] cost Cost from begin to selected point
 * @param[in] predec Predecessor of this point
 */
template<typename T>
void DepthFirstSearch2D<T>::addToFringe(const T cost, const size_t ind, size_t predec)
{
    //
}

/**
 * @brief Computes the heuristic from current point to the goal as Euclidean Distance
 * @param[in] current Point to start
 * @return Euclidean distance to path goal
 */
template<typename T>
T DepthFirstSearch2D<T>::compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const
{
    const T dist = std::sqrt(pow(desired.getX() - current.getX(), 2) + pow(desired.getY() - current.getY(), 2));
    return dist;
}