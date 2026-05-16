/**
 * @file AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include "AStar2D.h"

/**
 * @brief Creates object to perform search on given plan
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
AStar2D<T>::AStar2D(const std::string filename) : SearchBase2D<T>(filename), prioQueue(makeComparator())
{
    //
}