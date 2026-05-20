/**
 * @file AStar2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_ASTAR_H
#define H_ASTAR_H

#include<queue>
#include<tuple>
#include<vector>

#include "SearchBase2D.h"

/**
 * @class AStar2D
 * @brief Class to perform a search by the A* algorithm on a given environment.
 */
template<typename T>
class AStar2D : public SearchBase2D<T> {
    private:
        using pointDistance = std::tuple<T, size_t>; /**< Element to represent distant information of a point and its index */

        /**
         * @brief Wrapper for sorting expression of points in priority queue
         * 
         *      Lambda needs to be wrapped into static function because lambdas cannot directly be defined as members.
         *      If the priority queue is not defined as member variable, the lambda expression can directly passed to the definition.
         */
        static auto makeComparator() {
            return [](const pointDistance& a, const pointDistance& b) {
                return std::get<0>(a) > std::get<0>(b);
            };
        }

        using Comparator = decltype(makeComparator()); /**< Defines the given lambda as comparison element */

        std::unique_ptr<std::priority_queue<pointDistance,
                            std::vector<pointDistance>,
                            Comparator>> prioQueue; /**< Priority queue to sort the following points to investigate by distance. */

        T compHeuristic(const Point2D<T>& current, const Point2D<T> &desired) const;
        T compHeuristicGoal(const Point2D<T>& current) const override;
        void addToFringe(const size_t ind, const T cost) override;

    public:
        AStar2D(const std::string& filename);
        void findPath(const Point2D<T>& start) override;
};

template class AStar2D<int>;
template class AStar2D<float>;
template class AStar2D<double>;

#endif // H_ASTAR_H