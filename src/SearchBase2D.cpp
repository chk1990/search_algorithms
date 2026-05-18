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
SearchBase2D<T>::SearchBase2D(const std::string& filename)
{
    this->grid = std::make_unique<Grid2D<T>>();
    this->grid.get()->importPlanFile(filename);

    //grid.get()->printContent();
    //grid.get()->printCoordinates();
}

/**
 * @brief Add a point to the path
 * @param[in] point Point to add
 */
template<typename T>
void SearchBase2D<T>::add2path(const Point2D<T>& point)
{
    // determine index of point
    size_t ind = grid.get()->getIndex(point);

    this->setPath(0, 0);
    this->path.get()->push_back(ind);
}

/**
 * @brief Declare a point as part of a path
 */
template <typename T>
void SearchBase2D<T>::setPath(const size_t col, const size_t row)
{
    Grid2D<T>* g = this->grid.get();
    size_t ind = g->index(col, row);
    this->path.get()->push_back(ind);
    
    g->setPath(col, row);
    g->setDiscovered(col, row);
}