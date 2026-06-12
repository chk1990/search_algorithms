/**
 * @file DepthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

 #include "DepthFirstSearch2D.h"

/**
 * @brief Initializes the path finding object
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
DepthFirstSearch2D<T>::DepthFirstSearch2D(const std::string& filename) : SearchBase2D<T>(filename, "bfs"),
                                                                         stack(std::make_unique<std::stack<size_t>>())
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