/**
 * @file BreadthFirstSearch2D.h
 * @author Christoph Kolhoff
 */

#include<cmath>

#include "BreadthFirstSearch2D.h"

/**
 * @brief Initializes the path finding object
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
BreadthFirstSearch2D<T>::BreadthFirstSearch2D(const std::string& filename) : SearchBase2D<T>(filename, "bfs"),
                                                                             queue(std::make_unique<std::queue<pathElement>>())
{
    //
}

/**
 * @brief Adds a point to the queue
 * @param[in] ind Index of point to add
 * @param[in] cost Cost from begin to selected point
 * @param[in] predec Predecessor of this point
 */
template<typename T>
void BreadthFirstSearch2D<T>::addToFringe(const T cost, const size_t ind, size_t predec)
{
    const pathElement elem = {cost, ind, predec};
    this->queue->push(elem);
}

/**
 * @brief Finds the path from start to goal if the path is available. The results as path and search tree are exported to files afterwards.
 * 
 * The file for the tree is structured as follows:
 * x1,y1,x2,y2
 */
template<typename T>
void BreadthFirstSearch2D<T>::findPath(const Point2D<T>& start)
{
    // Find path
    // =============================================
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

    this->setBegin(start);

    // put first child to the queue
    std::queue<pathElement>* q = this->queue.get();

    // initialize variables for evaluation if goal has been reached
    bool leave = false;
    size_t indSuccessor = 0;
    Point2D<T> successor;

    // collect all visited points for backtracking later
    const size_t indStartPt = this->getPointIndex(start);
    const pathElement initPt{0, indStartPt, indStartPt};

    this->addVisited(initPt);

    while(!q->empty()) {
        if(leave) {
            break;
        }

        const pathElement elem = queue->front();
        queue->pop();

        const size_t indCurrent = std::get<1>(elem);
        const Point2D<T> current = this->getCoordinates(indCurrent);
        const T cumulDistCurr = this->getCumulDist(indCurrent);

        for(T dX = -1; dX <= 1; ++dX) {
            for(T dY = -1; dY <= 1; ++dY) {
                if(leave) {
                    break;
                }

                if(dX == 0 && dY == 0) {
                    continue;
                }

                // determine successor and apply limitation
                T xVal = current.getX() + dX * step;
                xVal = std::max(xVal, minX);
                xVal = std::min(xVal, maxX);

                T yVal = current.getY() + dY * step;
                yVal = std::max(yVal, minY);
                yVal = std::min(yVal, maxY);

                successor = Point2D<T>(xVal, yVal);
                indSuccessor = this->getPointIndex(successor);
                
                // check if it containd an obstacle
                if(this->isObstacle(indSuccessor)) {
                    continue;
                }

                if(this->isDiscovered(indSuccessor)) {
                    continue;
                }

                // can be set as discovered and skipped afterwards because A* acts optimal
                this->setDiscovered(indSuccessor);

                // direct distance from current point to next one
                const T distCurrSucc = this->compHeuristic(successor, current);

                // find the predecessor point in visited
                const T actualCost = cumulDistCurr + distCurrSucc;
                const pathElement pt = {actualCost, indSuccessor, indCurrent};
                this->addVisited(pt);

                if(this->isGoal(successor)) {
                    leave = true;
                }

                // add new element to queue
                this->addToFringe(actualCost, indSuccessor, indCurrent);

                if(leave) {
                    break;
                }
            }
        }
    }

    while(!q->empty()) {
        q->pop();
    }

    // Backtracking and export
    // =============================================
    this->backtrack();
    
    this->exportPath();
    this->exportTree();
}

/**
 * @brief Computes the heuristic from current point to the goal as Euclidean Distance
 * @param[in] current Point to start
 * @return Euclidean distance to path goal
 */
template<typename T>
T BreadthFirstSearch2D<T>::compHeuristic(const Point2D<T>& current, const Point2D<T>& desired) const
{
    const T dist = std::sqrt(pow(desired.getX() - current.getX(), 2) + pow(desired.getY() - current.getY(), 2));
    return dist;
}