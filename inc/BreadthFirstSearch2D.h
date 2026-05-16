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
    std::queue<T> queue;
};

template class BreadthFirstSearch2D<int>;
template class BreadthFirstSearch2D<float>;
template class BreadthFirstSearch2D<double>;

#endif // H_BREADTH_FIRST_SEARCH_H