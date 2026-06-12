/**
 * @file BreadthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#include "BreadthFirstSearch2D.h"

/**
 * @brief Initializes the path finding object
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
BreadthFirstSearch2D<T>::BreadthFirstSearch2D(const std::string& filename) : SearchBase2D<T>(filename, "bfs"),
                                                                             queue(std::make_unique<std::queue<size_t>>())
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
void BreadthFirstSearch2D<T>::addToFringe(const T cost, const size_t ind, size_t predec)
{
    //
}

/**
 * @brief Finds the path from start to goal if the path is available. The results as path and search tree are exported to files afterwards.
 * 
 * The file for the tree is structured as follows:
 * x1,y1,x2,y2
 */
template<typename T>
void BreadthFirstSearch2D<T>::findPath(const Point2D<T>& start)
{
    // Find path
    // =============================================
    const size_t width = this->getGridWidth();
    const size_t height = this->getGridHeight();
    const Point2D<T> ptLim1 = this->getMinLimPoint();
    const Point2D<T> ptLim2 = this->getMaxLimPoint();

    // coordinates of grid limits
    const T minX = ptLim1.getX();
    const T maxX = ptLim2.getX();
    const T minY = ptLim1.getY();
    const T maxY = ptLim2.getY();

    const T step = this->getGridStep();
}