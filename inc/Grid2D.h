/**
 * @file Grid2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_GRID_2D_H
#define H_GRID_2D_H

#include<cstddef>
#include<iostream>
#include<memory>

#include "Occupancy.h"
#include "Point2D.h"

/**
 * @class Grid2D
 * @brief Handles information of a 2D grid
 * 
 * The map is represented by dimensions in x and y. Width and height are represented by x and y respectively. All distances in x- and y-direction are equidistant.
 * The type T can be int, float, double.
 */
template<typename T>
class Grid2D
{
   private:
      std::unique_ptr<Point2D<T>[]> coordinates; /**< Coordinates of the map */
      std::unique_ptr<Occupancy[]> occupancy; /**< Content of the map. */
      std::unique_ptr<bool[]> discovered; /**< Discovery state */

      size_t height; /**< Height of the map */
      size_t width;  /**< Width of the map */
      T step; /**< Step in x- and y- direction between two points */

      void populatePoints();
      void populatePoints(const T xOff, const T yOff);

   public:
      Grid2D();
      Grid2D(const size_t width, const size_t height, const T step);
      Grid2D(const size_t width, const size_t height, const T step, const T offX, const T offY);

      void setFree(const size_t col, const size_t row);
      void setObstacle(const size_t ind);
      void setObstacle(const size_t col, const size_t row);
      void setPath(const size_t col, const size_t row);   
      void setPath(const size_t ind);
      void setPath(const Point2D<T>& pt);
      void setDiscovered(const size_t col, const size_t row);
      void setDiscovered(const size_t ind);
      void setUndiscovered(const size_t col, const size_t row);
      bool isFree(const size_t col, const size_t row) const;
      bool isPath(const size_t ind) const;
      bool isPath(const Point2D<T>& pt) const;
      bool isPath(const size_t col, const size_t row) const;
      bool isObstacle(const size_t ind) const;
      bool isObstacle(const size_t col, const size_t row) const;
      bool isDiscovered(const size_t col, const size_t row) const;
      bool isDiscovered(const size_t ind) const;
      size_t index(const size_t col, const size_t row) const;

      Point2D<T>& getCoordinates(const size_t col, const size_t row) const;
      Point2D<T>& getCoordinates(const size_t ind) const;
      T getStep() const;
      size_t getHeight() const;
      size_t getWidth() const;
      size_t index(const Point2D<T>& point) const;
      void printContent() const;
      void printCoordinates() const;
      void exportPlanFile(const std::string& filename) const;
      void importPlanFile(const std::string& filename);
};

template class Grid2D<int>;
template class Grid2D<float>;
template class Grid2D<double>;

#endif // H_GRID_2D_H