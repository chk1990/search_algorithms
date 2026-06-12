/**
 * @file DepthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_DEPTH_FIRST_SEARCH_H
#define H_DEPTH_FIRST_SEARCH_H

#include<stack>

#include "SearchBase2D.h"

template<typename T>
class DepthFirstSearch2D : public SearchBase2D<T> {
    private:
        using pathElement = std::tuple<T, size_t, size_t>; /**< Element to represent distant information of a point, its index and its predecessor*/

        std::unique_ptr<std::stack<pathElement>> stack;

        void addToFringe(const T cost, const size_t ind, size_t predec);
        T compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const;

    public:
        DepthFirstSearch2D(const std::string& filename);

        void findPath(const Point2D<T>& start, const Point2D<T>& goal);
};

template class DepthFirstSearch2D<int>;
template class DepthFirstSearch2D<float>;
template class DepthFirstSearch2D<double>;

#endif // H_DEPTH_FIRST_SEARCH_H