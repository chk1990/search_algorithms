/**
 * @file DepthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_DEPTH_FIRST_SEARCH_H
#define H_DEPTH_FIRST_SEARCH_H

#include<stack>

#include "SearchBase2D.h"

template<typename T>
class DepthFirstSearch2D  : public SearchBase2D<T> {
    std::stack<T> stack;
};

template class DepthFirstSearch2D<int>;
template class DepthFirstSearch2D<float>;
template class DepthFirstSearch2D<double>;

#endif // H_DEPTH_FIRST_SEARCH_H