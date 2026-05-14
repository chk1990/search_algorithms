/**
 * @file Grid2D.h
 * @author Christoph Kolhoff
 */

#ifndef H_GRID_2D_H
#define H_GRID_2D_H

#include <cstddef>
#include <memory>

#include "Point2D.h"

/**
 * @class Occupancy
 * @brief Describes the state of a point of the map
 */
enum Occupancy 
{
   UNEXPLORED,
   FREE,
   OBSTACLE
};

/**
 * @class Grid2D
 * @brief Handles information of a 2D grid
 * 
 * The map is represented by dimensions in x and y. Width and height are represented by x and y respectively.
 * The type T can be int, float, double.
 */
template<typename T>
class Grid2D
{
   private:
      std::unique_ptr<Point2D<T>[]> coordinates; /**< Coordinates of the map */
      std::unique_ptr<Occupancy[]> occupancy; /**< Content of the map. */

      size_t height; /**< Height of the map */
      size_t width;  /**< Width of the map */
      T step; /**< Step in x- and y- direction between two points */

      size_t index(const size_t col, const size_t row) const;

   public:
      Grid2D(const size_t width, const size_t height, const T step);
      Grid2D(const size_t width, const size_t height, const T step, const T offX, const T offY);

      void setOccupancyUnexplored(const size_t col, const size_t row);
      void setOccupancyFree(const size_t col, const size_t row);
      void setOccupancyObstacle(const size_t col, const size_t row);

      Point2D<T> getCoordinates(const size_t col, const size_t row) const;
      T getStep() const;
      size_t getHeight() const;
      size_t getWidth() const;
      void printContent() const;
      void printCoordinates() const;
};

#endif // H_GRID_2D_H