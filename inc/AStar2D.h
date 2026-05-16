/**
 * @file AStar2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_ASTAR_H
#define H_ASTAR_H

#include<queue>

#include "SearchBase2D.h"

template<typename T>
class AStar2D : public SearchBase2D<T> {
    private:
        std::priority_queue<T> prQueue;
};

template class AStar2D<int>;
template class AStar2D<float>;
template class AStar2D<double>;

#endif // H_ASTAR_H