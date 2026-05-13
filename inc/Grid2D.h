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
 * @class Grid2D
 * @brief Handles information of a 2D grid
 * 
 * The map is represented by dimensions in x and y. Width and heigth are represented by x and y respectively.
 * The type T can be int, float, double.
 */
template<typename T>
class Grid2D
{
   private:
      std::unique_ptr<Point2D<T>[]> coordinates; /**< Coordinates of the map */
      std::unique_ptr<uint8_t[]> occupancy;   /**< Content of the map */

      size_t heigth; /**< Heigth of the map */
      size_t width;  /**< Width of the map */
      T step; /**< Step in x- and y- direction between two points */

      size_t index(const size_t col, const size_t row) const;

   public:
      Grid2D(const size_t heigth, const size_t width, const T step);
      Grid2D(const size_t heigth, const size_t width, const T step, const T offX, const T offY);

      size_t getHeigt() const;
      size_t getWidth() const;
};

#endif // H_GRID_2D_H