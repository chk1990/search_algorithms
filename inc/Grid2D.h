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
 */
class Grid2D
{
   private:
      std::unique_ptr<Point2D[]> coordinates; /**< Coordinates of the map */
      std::unique_ptr<uint8_t[]> occupancy;   /**< Content of the map */

      size_t heigth; /**< Heigth of the map */
      size_t width;  /**< Width of the map */

      size_t index(const size_t row, const size_t col) const;

   public:
      Grid2D(size_t heigth, size_t width);
};

#endif // H_GRID_2D_H