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
        std::queue<T> queue;

    public:
        void findPath(const Point2D<T>& start, const Point2D<T>& goal);
};

template class BreadthFirstSearch2D<int>;
template class BreadthFirstSearch2D<float>;
template class BreadthFirstSearch2D<double>;

#endif // H_BREADTH_FIRST_SEARCH_H