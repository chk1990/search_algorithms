/**
 * @file SearchBase2D.cpp
 * @author Christoph Kolhoff
 */

#include "SearchBase2D.h"

/**
 * @brief Initialize search environment
 * @param[in] filename Name of file that contains the plan
 */
template<typename T>
SearchBase2D<T>::SearchBase2D(const std::string& filename) : goal(std::make_unique<Point2D<T>>()),
                                                             grid(std::make_unique<Grid2D<T>>()),
                                                             path(std::make_unique<std::vector<size_t>>())
{
    this->grid.get()->importPlanFile(filename);
    //this->setGoal(Point2D<T>(static_cast<T>(0), static_cast<T>(0)));
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
 * @brief Add a point to the path
 * @param[in] point Point to add
 */
template<typename T>
void SearchBase2D<T>::add2path(const Point2D<T>& point)
{
    size_t ind = this->grid.get()->index(point);
    this->setPath(point);
    this->path.get()->emplace_back(ind);
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
    this->setPath(ind);

    std::vector<size_t>* p = this->path.get();

    if(p->size() == 0) {
        p->emplace_back(ind);
    } else {
        p->at(0) = ind;
    }

    this->setDiscovered(ind);

    this->addToFringe(ind, 0, -1);
}

/**
 * @brief Set goals of path
 * @param[in] point Goal point
 * @note The point is not added to internal path. If this method is not called, the origin is set as goal.
 */
template <typename T>
void SearchBase2D<T>::setGoal(const Point2D<T>& point)
{
    this->goal = std::make_unique<Point2D<T>>(point);

    // determine index
    Grid2D<T>* g = this->grid.get();
    size_t ind = g->index(point);

    //g->setPath(ind);
    this->setGridGoal(ind);
    this->setDiscovered(ind);
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
    /*
    T xGoal = this->goal.get()->getX();
    T yGoal = this->goal.get()->getY();
    T xThis = point.getX();
    T yThis = point.getY();

    return xGoal == xThis && yGoal == yThis;
    */
   Point2D<T> goal = *(this->goal.get());
   return point == goal;
}

/**
 * @brief Gets goals of path
 */
template <typename T>
Point2D<T>& SearchBase2D<T>::getGoal() const
{
    return *(this->goal.get());
}

/**
 * @brief Declare a point as part of a path
 * @param[in] ind Index of interest
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getPath(const size_t ind) const
{
    const std::vector<size_t> pth = *(this->path.get());
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