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
 * @brief Add a point to the path
 * @param[in] point Point to add
 */
template<typename T>
void SearchBase2D<T>::add2path(const Point2D<T>& point)
{
    // determine index of point
    size_t ind = this->grid.get()->getIndex(point);

    this->setPath(ind);
    this->path.get()->push_back(ind);
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

    this->path.get()->push_back(ind);
}

/**
 * @brief Declare a point as part of a path
 * @param[in] col Column of interest
 * @param[in] row Row of interest
 */
template <typename T>
void SearchBase2D<T>::setPath(const size_t col, const size_t row)
{
    Grid2D<T>* g = this->grid.get();
    size_t ind = g->index(col, row);
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
    this->add2path(point);
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
    size_t ind = g->getIndex(point);

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