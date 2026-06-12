/**
 * @file BreadthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_BREADTH_FIRST_SEARCH_H
#define H_BREADTH_FIRST_SEARCH_H

#include<queue>

#include "SearchBase2D.h"

template<typename T>
class BreadthFirstSearch2D : public SearchBase2D<T> {
    private:
        using pathElement = std::tuple<T, size_t, size_t>; /**< Element to represent distant information of a point, its index and its predecessor*/

        std::unique_ptr<std::queue<pathElement>> queue;

        void addToFringe(const T cost, const size_t ind, size_t predec);
        T compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const;

    public:
        BreadthFirstSearch2D(const std::string& filename);

        void findPath(const Point2D<T>& start);
};

template class BreadthFirstSearch2D<int>;
template class BreadthFirstSearch2D<float>;
template class BreadthFirstSearch2D<double>;

#endif // H_BREADTH_FIRST_SEARCH_H