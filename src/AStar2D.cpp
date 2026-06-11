/**
 * @file AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include<algorithm>
#include<cmath>
#include<fstream>

#include "AStar2D.h"

/**
 * @brief Creates object to perform search on given plan
 * 
 * @param[in] filename Name of the file containing the plan
 */
template<typename T>
AStar2D<T>::AStar2D(const std::string& filename) : SearchBase2D<T>(filename, "astar"),
                                                   prioQueue(std::make_unique<std::priority_queue<pathElement,
                                                             std::vector<pathElement>,
                                                             comparator>>())
{
    //
}

/**
 * @brief Finds the path from start to goal if the path is available. The results as path and search tree are exported to files afterwards.
 * 
 * The file for the tree is structured as follows:
 * x1,y1,x2,y2
 * 
 * @param[in] start Point to start
 */
template<typename T>
void AStar2D<T>::findPath(const Point2D<T>& start)
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

    // put all children to the queue
    priorityQueue* pq = this->prioQueue.get();
    this->setBegin(start);

    // initialize variables for evaluation if goal has been reached
    bool leave = false;
    size_t indSuccessor = 0;
    Point2D<T> successor;

    // collect all visited points for backtracking later
    const size_t indStartPt = this->getPointIndex(start);
    const pathElement initPt{0, indStartPt, indStartPt};

    std::vector<pathElement> visited;
    visited.emplace_back(initPt);

    while(!pq->empty()) {

        if(leave) {
            break;
        }

        const pathElement elem = pq->top();
        pq->pop();

        const size_t indCurrent = std::get<1>(elem);
        const Point2D<T> current = this->getCoordinates(indCurrent);

        auto visitCrit = [indCurrent](const pathElement& ptInfoVec) {
            // find the point entity that has a given current index
            const size_t indCurr = std::get<1>(ptInfoVec);
            return indCurr == indCurrent;
        };

        typename std::vector<pathElement>::iterator it;
        it = std::find_if(visited.begin(), visited.end(), visitCrit);

        // actual cost from the current node for which the children are investigated
        const T cumulDistCurr = std::get<0>(*it);

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

                // direct distance from current node to next one
                const T distCurrSucc = this->compHeuristic(successor, current);

                // heuristic from successor to goal
                const T heurDistSucc = this->compHeuristicGoal(successor);

                // find the predecessor node in visited
                const T actualCost = cumulDistCurr + distCurrSucc;
                const pathElement pt = {actualCost, indSuccessor, indCurrent};
                visited.emplace_back(pt);

                if(this->isGoal(successor)) {
                    leave = true;
                }
                
                // add new element to priority queue
                const T succHeur = actualCost + heurDistSucc;
                this->addToFringe(succHeur, indSuccessor, indCurrent);

                if(leave) {
                    break;
                }
            }
        }
    }

    while(!pq->empty()) {
        pq->pop();
    }

    // Backtracking
    // =============================================
    const pathElement currVisited = visited.back();
    size_t currInd = std::get<1>(currVisited);
    size_t predInd = std::get<2>(currVisited);

    this->add2path(currInd);

    currInd = predInd;

    while(true) {
        // determine previously visited point
        typename std::vector<pathElement>::iterator it;

        auto backtrackCrit = [currInd](const pathElement& visitPt) {
            // find the point with a specific current index
            const size_t indVisited = std::get<1>(visitPt);
            return indVisited == currInd;
        };

        it = std::find_if(visited.begin(), visited.end(), backtrackCrit);

        currInd = std::get<1>(*it);
        predInd = std::get<2>(*it);

        this->add2path(currInd);

        if(currInd == predInd) {
            break;
        }

        currInd = predInd;
    }

    // Export path and search tree
    // =============================================
    this->exportPath();

    const size_t len = this->getFilename().size();
    std::string baseName = this->getFilename().substr(0, len-4);

    std::ofstream fileTree;
    fileTree.open(baseName + "_tree.dat");
    if(!fileTree.is_open()) {
        perror("Failed to open tree file");
        return;
    }

    for(const pathElement& ptInfo : visited) {
        const size_t indEnd = std::get<1>(ptInfo);
        const size_t indStart = std::get<2>(ptInfo);

        const Point2D<T> startPt = this->getPoint(indStart);
        const Point2D<T> endPt = this->getPoint(indEnd);

        const T x1 = startPt.getX();
        const T y1 = startPt.getY();
        const T x2 = endPt.getX();
        const T y2 = endPt.getY();

        fileTree << x1 << "," << y1 << "," << x2 << "," << y2 << std::endl;
    }

    fileTree.close();
}

/**
 * @brief Print all elements of the priority queue
 */
template<typename T>
void AStar2D<T>::printPrioQueue() const
{
    priorityQueue* pq = this->prioQueue.get();
    while(!pq->empty()) {
        pathElement pd = pq->top();
        pq->pop();
        this->printpathElement(pd);
    }
}

/**
 * @brief Adds a point to the priority queue
 * @param[in] ind Index of point to add
 * @param[in] cost Cost from begin to selected node
 * @param[in] predec Predecessor of this node
 */
template<typename T>
void AStar2D<T>::addToFringe(const T cost, const size_t ind, size_t predec)
{
    const pathElement elem = {cost, ind, predec};
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
 * @brief Computes the heuristic from current point to the desired point as Euclidean Distance. Any other valid heuristic can be used as far as it is admissible and consistent.
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

/**
 * @brief Print the content of a point info set
 * @param[in] ptInfo Point info as needed
 */
template<typename T>
void AStar2D<T>::printpathElement(const pathElement ptInfo) const
{
    std::cout << "Dist = " << std::get<0>(ptInfo) << "; Current = " << std::get<1>(ptInfo) << "; Predecessor = " << std::get<2>(ptInfo) << std::endl;
}