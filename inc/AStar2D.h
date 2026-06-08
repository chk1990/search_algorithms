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
        using pointInfo = std::tuple<T, size_t, size_t>; /**< Element to represent distant information of a point, its index and its predecessor*/

        /**
         * @brief Wrapper for sorting expression of points in priority queue
         * 
         *      Lambda needs to be wrapped into static function because lambdas cannot directly be defined as members.
         *      If the priority queue is not defined as member variable, the lambda expression can directly passed to the definition.
         */
        static auto makeComparator() {
            return [](const pointInfo& a, const pointInfo& b) {
                return std::get<0>(a) > std::get<0>(b);
            };
        }

        using comparator = decltype(makeComparator()); /**< Defines the given lambda as comparison element */
        using priorityQueue = std::priority_queue<pointInfo, std::vector<pointInfo>, comparator>; /**< Represent the data structure of the used priority queue */

        std::unique_ptr<priorityQueue> prioQueue; /**< Priority queue to sort the following points to investigate by distance. */

        T compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const;
        T compHeuristicGoal(const Point2D<T>& current) const override;
        void addToFringe(const T cost, const size_t ind, size_t predec) override;
        void printPointInfo(const pointInfo ptInfo) const;

    public:
        AStar2D(const std::string& filename);
        void findPath(const Point2D<T>& start) override;
        void printPrioQueue() const;
};

template class AStar2D<int>;
template class AStar2D<float>;
template class AStar2D<double>;

#endif // H_ASTAR_H