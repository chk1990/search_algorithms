/**
 * @file SearchBase2D.cpp
 * @author Christoph Kolhoff
 */

#include<algorithm>
#include<fstream>

#include "SearchBase2D.h"

/**
 * @brief Initialize search environment
 * @param[in] filename Name of file that contains the plan
 */
template<typename T>
SearchBase2D<T>::SearchBase2D(const std::string& filename, const std::string& algName) : grid(std::make_unique<Grid2D<T>>()),
                                                             path(std::make_unique<std::deque<size_t>>()),
                                                             fileName(filename),
                                                             algorithmName(algName)
{
    this->grid.get()->importPlanFile(fileName);
}

/**
 * @brief Print the content of the grid
 */
template<typename T>
void SearchBase2D<T>::printGrid() const
{
    this->grid.get()->printContent();
}

/**
 * @brief Returns the width of the grid
 */
template<typename T>
size_t SearchBase2D<T>::getGridWidth() const
{
    return this->grid.get()->getWidth();
}

/**
 * @brief Returns the height of the grid
 */
template<typename T>
size_t SearchBase2D<T>::getGridHeight() const
{
    return this->grid.get()->getHeight();
}


/**
 * @brief Returns the step size of the grid
 */
template<typename T>
T SearchBase2D<T>::getGridStep() const
{
    return this->grid.get()->getStep();
}

/**
 * @brief Declare a point as part of a path
 * @param[in] point Point to add
 */
template<typename T>
void SearchBase2D<T>::setPath(const Point2D<T>& point)
{
    size_t ind = this->grid.get()->index(point);
    this->setPath(ind);
}

/**
 * @brief Declare a point as part of a path
 * @param[in] ind Index of interest
 */
template <typename T>
void SearchBase2D<T>::setPath(const size_t ind)
{
    Grid2D<T>* g = this->grid.get();
    g->setPath(ind);
    g->setDiscovered(ind);

    this->path.get()->emplace_back(ind);
}

/**
 * @brief Declare a point as part of a path
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void SearchBase2D<T>::setPath(const size_t col, const size_t row)
{
    const Grid2D<T>* g = this->grid.get();
    const size_t ind = g->index(col, row);
    this->setPath(ind);
}

/**
 * @brief Set begin of path
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 * @pre SearchBase2D<T>::setGoal() must be called before
 */
template <typename T>
void SearchBase2D<T>::setBegin(const Point2D<T>& point)
{
    const size_t ind = this->grid.get()->index(point);
    this->setGridStart(ind);

    this->setDiscovered(ind);
    this->addToFringe(0, ind, ind);
}

/**
 * @brief Set goals of path
 * @param[in] point Goal point
 * @note The point is not added to internal path. If this method is not called, the origin is set as goal.
 */
template <typename T>
void SearchBase2D<T>::setGoal(const Point2D<T>& point)
{
    this->goal = point;

    // determine index
    Grid2D<T>* g = this->grid.get();
    size_t ind = g->index(point);

    this->setGridGoal(ind);
}

/**
 * @brief Sets the point as goal in grid
 * @param[in] ind Index of interest
 */
template <typename T>
void SearchBase2D<T>::setGridGoal(const size_t ind)
{
    this->grid.get()->setGoal(ind);
}

/**
 * @brief Checks if the given point is the goal
 * @param[in] point Point to investigate
 */
template <typename T>
bool SearchBase2D<T>::isGoal(const Point2D<T>& point) const
{
   Point2D<T> goal = this->goal;
   return point == goal;
}

/**
 * @brief Gets goals of path
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getGoal() const
{
    return this->goal;
}

/**
 * @brief Declare a point as part of a path
 * @param[in] ind Index of interest
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getPath(const size_t ind) const
{
    const std::deque<size_t> pth = *(this->path.get());
    const size_t indPt = pth[ind];

    const Grid2D<T>* g = this->grid.get();
    const Point2D<T> pt = g->getCoordinates(indPt);
    
    return pt;
}

/**
 * @brief Get the bottom-left point of the grid
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getMinLimPoint() const
{
    Point2D<T> pt = this->grid.get()->getCoordinates(0);

    return pt;
}

/**
 * @brief Get the top-right point of the grid
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getMaxLimPoint() const
{
    const size_t width = this->getGridWidth();
    const size_t height = this->getGridHeight();

    Point2D<T> pt = this->grid.get()->getCoordinates(width*height - 1);

    return pt;
}

/**
 * @brief Returns the point at the given location
 * @param[in] ind Index of point
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getCoordinates(const size_t ind) const
{
    return this->grid.get()->getCoordinates(ind);
}

/**
 * @brief Gets the point's index in the grid
 * @param[in] point Point of interest
 */
template <typename T>
size_t SearchBase2D<T>::getPointIndex(const Point2D<T>& point) const
{
    return this->grid.get()->index(point);
}

/**
 * @brief Checks if the point is discovered
 * @param[in] ind Index of point
 */
template <typename T>
bool SearchBase2D<T>::isDiscovered(const size_t ind) const
{
    return this->grid.get()->isDiscovered(ind);
}

/**
 * @brief Sets the state of the point as discovered
 * @param[in] point Point of interest
 */
template <typename T>
void SearchBase2D<T>::setDiscovered(const size_t ind)
{
    this->grid.get()->setDiscovered(ind);
}

/**
 * @brief Checks if the point is an obstacle
 * @param[in] ind Index of point
 */
template <typename T>
bool SearchBase2D<T>::isObstacle(const size_t ind) const
{
    return this->grid.get()->isObstacle(ind);
}

/**
 * @brief Determines the point's index in the grid
 * @param[in] ind Index of point
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getPoint(size_t ind) const
{
    return this->grid.get()->getCoordinates(ind);
}

/**
 * @brief Sets the current point as start in the grid
 * @param[in] ind Index of point
 */
template <typename T>
void SearchBase2D<T>::setGridStart(const size_t ind)
{
    this->grid.get()->setStart(ind);
}

/**
 * @brief Add a point index to the front of the path for backtracking
 * @param[in] ind Index of point
 */
template <typename T>
void SearchBase2D<T>::add2path(const size_t ind)
{
    this->path.get()->emplace_front(ind);
}

/**
 * @brief Print all node indices of the computed path
 */
template <typename T>
void SearchBase2D<T>::printPath() const
{
    for(const size_t ind : *(this->path.get())) {
        std::cout << ind << std::endl;
    }
}

/**
 * @brief Delivers name of the file with the plan to work on
 */
template <typename T>
std::string SearchBase2D<T>::getFilename() const
{
    return this->fileName;
}

/**
 * @brief Export the computed path to a file
 * The coordinates of one point of the path (x and y) are printed into the same row.
 */
template <typename T>
void SearchBase2D<T>::exportPath() const
{
    const size_t len = this->getFilename().size();
    const std::string baseName = this->getFilename().substr(0, len-4);

    std::ofstream filePath;
    filePath.open(baseName + "_" + this->getAlgorithmName() + "_path.dat");
    if(!filePath.is_open()) {
        perror("Failed to open path file");
        return;
    }

    for(const size_t indPath : *(this->path.get())) {
        const Point2D<T> pathPoint = this->getPoint(indPath);
        T x = pathPoint.getX();
        T y = pathPoint.getY();

        filePath << x << "," << y << std::endl;
    }

    filePath.close();
}

/**
 * @brief Export the computed path to a file
 * The coordinates of one point of the path (x and y) are printed into the same row.
 */
template <typename T>
void SearchBase2D<T>::exportTree() const
{
    const size_t len = this->getFilename().size();
    const std::string baseName = this->getFilename().substr(0, len-4);

    std::ofstream fileTree;
    fileTree.open(baseName + "_" + this->getAlgorithmName() + "_tree.dat");
    if(!fileTree.is_open()) {
        perror("Failed to open tree file");
        return;
    }

    for(const pathElement& ptInfo : this->visited) {
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
 * @brief Provides the name of the used algorithm
 */
template <typename T>
std::string SearchBase2D<T>::getAlgorithmName() const
{
    return this->algorithmName;
}

/**
 * @brief Adds a node to the visited ones
 * @param[in] elem Point information to add
 */
template <typename T>
void SearchBase2D<T>::addVisited(const pathElement& elem)
{
    this->visited.emplace_back(elem);
}

/**
 * @brief Backtracks the path that has been passed
 */
template <typename T>
void SearchBase2D<T>::backtrack()
{
    const pathElement currVisited = this->visited.back();
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

        it = std::find_if(this->visited.begin(), this->visited.end(), backtrackCrit);

        currInd = std::get<1>(*it);
        predInd = std::get<2>(*it);

        this->add2path(currInd);

        if(currInd == predInd) {
            break;
        }

        currInd = predInd;
    }
}

/**
 * @brief Determines the cummulated distance of a given point from the beginning
 * @param[in] ind 
 */
template <typename T>
T SearchBase2D<T>::getCumulDist(const size_t ind)
{
    auto visitCrit = [ind](const pathElement& ptInfoVec) {
            // find the point entity that has a given current index
            const size_t indCurr = std::get<1>(ptInfoVec);
            return indCurr == ind;
        };

        typename std::vector<pathElement>::iterator it;
        it = std::find_if(this->visited.begin(), this->visited.end(), visitCrit);

        // actual cost from the current node for which the children are investigated
        const T cumulDistCurr = std::get<0>(*it);

        return cumulDistCurr;
}