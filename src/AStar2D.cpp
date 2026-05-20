/**
 * @file AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include<cmath>

#include "AStar2D.h"

/**
 * @brief Creates object to perform search on given plan
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
AStar2D<T>::AStar2D(const std::string& filename) : SearchBase2D<T>(filename),
                                                   prioQueue(std::make_unique<std::priority_queue<pointDistance,
                                                   std::vector<pointDistance>,
                                                   Comparator>>())
{
    /*
    pointDistance p1 = {10.0, 12};
    pointDistance p2 = {6.0, 50};
    pointDistance p3 = {8.0, 4};

    auto* pq = this->prioQueue.get();
    pq->push(p1);
    pq->push(p2);
    pq->push(p3);

    while(pq->size() != 0) {
        pointDistance elem = pq->top();

        std::cout << "(" << std::get<0>(elem) << ", " << std::get<1>(elem) << ")" << std::endl;

        pq->pop();
    }
    */
}

/**
 * @brief Finds the path from start to goal if the path is available
 * @param[in] start Point to start
 * @todo complete and test
 */
template<typename T>
void AStar2D<T>::findPath(const Point2D<T>& start)
{
    this->printGrid();

    const size_t width = this->getGridWidth();
    const size_t height = this->getGridHeight();
    const Point2D<T> ptLim1 = this->getMinLimPoint();
    const Point2D<T> ptLim2 = this->getMaxLimPoint();

    // coordinates of grid limits
    const T minX = ptLim1.getX();
    const T maxX = ptLim2.getX();
    const T minY = ptLim1.getY();
    const T maxY = ptLim2.getY();

    // go through adjacent nodes
    const T currX = start.getX();
    const T currY = start.getY();
    const T step = this->getGridStep();

    for(int indY = -1; indY <= 1; ++indY) {
        for(int indX = -1; indX <= 1; ++indX) {
            if(indX == 0 && indY == 0) {
                continue;
            }

            // new point to investiate
            const T x = currX + step * indX;
            const T y = currY + step * indY;

            // check if r/c valid
            if(x > maxX || x < minX) {
                continue;
            }

            if(y > maxY || y < minY) {
                continue;
            }

            if(indX == 0 && indY == 0) {
                continue;
            }

            // compute heuristic
            const Point2D<T> pt(x, y);
            T heur = compHeuristicGoal(pt);

            // TODO: add to prio queue
        }
    }
}

/**
 * @brief Adds a point to the priority queue
 * @param[in] ind Index of point to add
 * @param[in] cost Cost determined by A* algorithm
 * @todo complete and test
 */
template<typename T>
void AStar2D<T>::addToFringe(const size_t ind, const T cost)
{
    const Point2D<T> currPt = this->getCoordinates(ind);
    const T estimDist = this->compHeuristicGoal(currPt);

    const pointDistance f = {estimDist, ind};
    //this->prioQueue->push(f); // TODO
}

/**
 * @brief Computes the heuristic from current point to the goal as Euclidean Distance
 * @param[in] current Point to start
 * @return Euclidean distance to path goal
 */
template<typename T>
T AStar2D<T>::compHeuristicGoal(const Point2D<T>& current) const
{
    const Point2D<T> goal = this->getGoal();
    return this->compHeuristic(current, goal);
}

/**
 * @brief Computes the heuristic from current point to the desired point as Euclidean Distance
 * @param[in] current Point to start
 * @param[in] desired Desired end of path
 * @return Euclidean distance of points
 */
template<typename T>
T AStar2D<T>::compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const
{
    const T dist = std::sqrt(pow(desired.getX() - current.getX(), 2) + pow(desired.getY() - current.getY(), 2));
    return dist;
}