/**
 * @file AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include<cmath>

#include "AStar2D.h"

/**
 * @brief Creates object to perform search on given plan
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
AStar2D<T>::AStar2D(const std::string& filename) : SearchBase2D<T>(filename), prioQueue(makeComparator())
{
    //
}

/**
 * @brief Finds the path from start to goal if the path is available
 * @param[in] start Point to start
 * @todo complete and test
 */
template<typename T>
void AStar2D<T>::findPath(const Point2D<T>& start)
{
    this->grid.get()->setPath(start);
    this->grid.get()->printContent();

    // go through adjacent nodes
    for(int indY = -1; indY <= 1; ++indY) {
        for(int indX = -1; indX <= 1; ++indX) {
            if(indX == 0 && indY == 0) {
                continue;
            }

            //
        }
    }
}

/**
 * @brief Computes the heuristic from current point to the goal as Euclidean Distance
 * @param[in] start Point to start
 * @param[in] goal Desired end of path
 * @return Euclidean distance of points
 */
template<typename T>
T AStar2D<T>::compHeuristic(const Point2D<T>& current, const Point2D<T>& goal) const
{
    T dist = std::sqrt(pow(goal.getX() - current.getX(), 2) + pow(goal.getY() - current.getY(), 2));
    return dist;
}