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
    //this->grid.get()->printContent();
    this->printGrid();

    const size_t width = this->getGridWidth();
    //this->grid.get()->getWidth();
    const size_t height = this->getGridHeight();
    //this->grid.get()->getHeight();
    const Point2D<T> ptLim1 = this->getMinLimPoint();
    const Point2D<T> ptLim2 = this->getMaxLimPoint();

    // coordinates of grid limits
    const T minX = ptLim1.getX();
    const T maxX = ptLim2.getX();
    const T minY = ptLim1.getY();
    const T maxY = ptLim2.getY();

    // go through adjacent nodes
    const T currX = start.getX();
    const T currY = start.getY();
    const T step = this->getGridStep();
    //this->grid.get()->getStep();

    for(int indY = -1; indY <= 1; ++indY) {
        for(int indX = -1; indX <= 1; ++indX) {
            if(indX == 0 && indY == 0) {
                continue;
            }

            // new point to investiate
            const T x = currX + step * indX;
            const T y = currY + step * indY;

            /*
            // check if r/c valid
            if(x >= || x <= ) {
                continue;
            }

            if(y >= || y <= ) {
                continue;
            }
            */

            const Point2D<T> pt(x, y);

            // compute heuristic
            T heur = compHeuristic(start, pt);
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
    const T dist = std::sqrt(pow(goal.getX() - current.getX(), 2) + pow(goal.getY() - current.getY(), 2));
    return dist;
}