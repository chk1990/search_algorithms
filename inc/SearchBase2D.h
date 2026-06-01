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
    protected:
        std::unique_ptr<Point2D<T>> goal; /**< Goal to be found */
        std::unique_ptr<Grid2D<T>> grid; /**< Contains information on the points on the grid */
        std::unique_ptr<std::vector<size_t>> path; /**< All points of the path found by the algorithm */

        void setBegin(const Point2D<T>& point);
        void setPath(const size_t col, const size_t row);
        void setPath(const size_t ind);
        void setPath(const Point2D<T>& point);
        void add2path(const Point2D<T>& point);
        virtual void addToFringe(const size_t ind, const T cost) = 0;
        virtual T compHeuristicGoal(const Point2D<T>& current) const = 0;

    public:
        SearchBase2D(const std::string& filename);
        ~SearchBase2D() {};

        virtual void findPath(const Point2D<T>& start) = 0;
        void setGoal(const Point2D<T>& point);
        Point2D<T>& getGoal() const;
        Point2D<T> getPath(const size_t ind) const;
        size_t getGridWidth() const;
        size_t getGridHeight() const;
        size_t getGridStep() const;
        size_t getPointIndex(const Point2D<T>& point) const;
        bool isDiscovered(size_t ind) const;
        void setDiscovered(const size_t ind);
        Point2D<T> getMinLimPoint() const;
        Point2D<T> getMaxLimPoint() const;
        Point2D<T> getCoordinates(const size_t ind) const;

        void printGrid() const;
};

template class SearchBase2D<int>;
template class SearchBase2D<float>;
template class SearchBase2D<double>;

#endif // H_SEARCH_BASE_H