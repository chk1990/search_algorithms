/**
 * @file SearchBase.h
 * @author Christoph Kolhoff
 */

#ifndef H_SEARCH_BASE_H
#define H_SEARCH_BASE_H

#include<string>
#include<vector>

#include "Grid2D.h"

/**
 * @class SearchBase2D
 * @brief Class to implement basic search functions
 */
template<typename T>
class SearchBase2D {
    private:
        Point2D<T> goal; /**< Goal to be found */

    protected:
        std::unique_ptr<Grid2D<T>> grid; /**< Contains information on the points on the grid */
        std::unique_ptr<std::vector<size_t>> path; /**< All points of the path found by the algorithm */

        void add2path(const Point2D<T>& point);
        void setPath(const size_t col, const size_t row);
        void setPath(const size_t ind);

    public:
        SearchBase2D(const std::string& filename);
        ~SearchBase2D() {};

        virtual void findPath(const Point2D<T>& start) = 0;
        void setBegin(const Point2D<T>& point);
        void setGoal(const Point2D<T>& point);
};

template class SearchBase2D<int>;
template class SearchBase2D<float>;
template class SearchBase2D<double>;

#endif // H_SEARCH_BASE_H