/**
 * @file AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include<algorithm>
#include<cmath>

#include "AStar2D.h"

/**
 * @brief Creates object to perform search on given plan
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
AStar2D<T>::AStar2D(const std::string& filename) : SearchBase2D<T>(filename),
                                                   prioQueue(std::make_unique<std::priority_queue<pointInfo,
                                                   std::vector<pointInfo>,
                                                   comparator>>())
{
    //
}

/**
 * @brief Finds the path from start to goal if the path is available
 * @param[in] start Point to start
 * @todo Ensure that goal is captured in nested loops
 * @todo Exit from nested loops
 * @todo Track current point in each loop
 */
template<typename T>
void AStar2D<T>::findPath(const Point2D<T>& start)
{
    const size_t width = this->getGridWidth();
    const size_t height = this->getGridHeight();
    const Point2D<T> ptLim1 = this->getMinLimPoint();
    const Point2D<T> ptLim2 = this->getMaxLimPoint();

    // coordinates of grid limits
    const T minX = ptLim1.getX();
    const T maxX = ptLim2.getX();
    const T minY = ptLim1.getY();
    const T maxY = ptLim2.getY();

    const T step = this->getGridStep();

    // put all children to the queue
    priorityQueue* pq = this->prioQueue.get();
    this->setBegin(start);

    while(!pq->empty()) {
        const pointInfo elem = pq->top();
        pq->pop();

        const size_t currentInd = std::get<1>(elem);
        const Point2D<T> current = this->getCoordinates(currentInd);

        for(T dX = -1; dX <= 1; ++dX) {
            for(T dY = -1; dY <= 1; ++dY) {
                if(dX == 0 && dY == 0) {
                    continue;
                }

                // determine successor and apply limitation
                T xVal = current.getX() + dX * step;
                if(xVal < minX) {
                    xVal = minX;
                }

                if(xVal > maxX) {
                    xVal = maxX;
                }

                T yVal = current.getY() + dY * this->getGridStep();
                //std::cout << yVal << std::endl;
                if(yVal < minY) {
                    yVal = minY;
                }

                if(yVal > maxY) {
                    yVal = maxY;
                }

                const Point2D<T> successor(xVal, yVal);
                const size_t indSuccessor = this->getPointIndex(successor);
                
                // check if it containd an obstacle
                if(this->isObstacle(indSuccessor)) {
                    continue;
                }

                if(this->isGoal(successor)) {
                    std::cout << "FOUND" << std::endl;
                    break;
                    break;
                    break;
                }

                if(this->isDiscovered(indSuccessor)) {
                    continue;
                } else {
                    this->setDiscovered(indSuccessor);
                    //this->setPath(indSuccessor);
                }

                // cummulated distance from beginning to current node
                const T cumulDist = std::get<0>(elem);

                // direct distance from current node to next one
                const T distCurrSucc = this->compHeuristic(successor, current);

                // heuristic from successor to goal
                const T heurDistSucc = this->compHeuristicGoal(successor);

                // summing all distances and heuristics up
                const T succHeur = heurDistSucc + cumulDist + distCurrSucc;
                
                // add new element tp priority queue
                this->addToFringe(indSuccessor, succHeur, currentInd);
            }
        }
    }
    
    // print elements of priority queue
    //this->printPrioQueue();
}

/**
 * @brief Print all elements of the priority queue
 */
template<typename T>
void AStar2D<T>::printPrioQueue() const
{
    priorityQueue* pq = this->prioQueue.get();
    while(!pq->empty()) {
        pointInfo pd = pq->top();
        pq->pop();
        std::cout << "(" << std::get<0>(pd) << " " << std::get<2>(pd) << " " << std::get<1>(pd) << ")" << std::endl;
    }
}

/**
 * @brief Adds a point to the priority queue
 * @param[in] ind Index of point to add
 * @param[in] cost Cost from begin to selected node
 * @param[in] predec Predecessor of this node
 */
template<typename T>
void AStar2D<T>::addToFringe(const size_t ind, const T cost, size_t predec)
{
    const pointInfo elem = {cost, ind, predec};
    this->prioQueue->push(elem);
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