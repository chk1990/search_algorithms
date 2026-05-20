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
SearchBase2D<T>::SearchBase2D(const std::string& filename) : goal(std::make_unique<Point2D<T>>()), grid(std::make_unique<Grid2D<T>>()), path(std::make_unique<std::vector<size_t>>())
{
    this->grid.get()->importPlanFile(filename);
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
size_t SearchBase2D<T>::getGridStep() const
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
 */
template <typename T>
void SearchBase2D<T>::setBegin(const Point2D<T>& point)
{
    const size_t ind = this->grid.get()->index(point);
    this->grid->setPath(ind);

    std::vector<size_t>* p = this->path.get();

    if(p->size() == 0) {
        p->emplace_back(ind);
    } else {
        p->at(0) = ind;
    }

    const T cost = this->compHeuristicGoal(point);

    this->addToFringe(ind, cost);
}

/**
 * @brief Set goals of path
 * @param[in] point Goal point
 * @post The point is not added to internal path
 */
template <typename T>
void SearchBase2D<T>::setGoal(const Point2D<T>& point)
{
    this->goal = std::make_unique<Point2D<T>>(point);

    // determine index
    Grid2D<T>* g = this->grid.get();
    size_t ind = g->index(point);

    g->setPath(ind);
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

template <typename T>
Point2D<T> SearchBase2D<T>::getMinLimPoint() const
{
    Point2D<T> pt = this->grid.get()->getCoordinates(0);

    return pt;
}

/**
 * @brief
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
 * @brief
 * @param[in] ind Index of point to 
 */
template <typename T>
Point2D<T> SearchBase2D<T>::getCoordinates(const size_t ind) const
{
    return this->grid.get()->getCoordinates(ind);
}