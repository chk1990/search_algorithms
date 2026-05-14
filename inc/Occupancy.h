/**
 * @file Occupancy.h
 * @author Christoph Kolhoff
 */

#ifndef H_OCCUPANCY_H
#define H_OCCUPANCY_H

/**
 * @enum Occupancy
 * @brief Describes the state of a point of the map
 */
enum Occupancy
{
   UNEXPLORED, /**< Point is not explored or somehow onknown */
   FREE, /**< Point is free and can be accessed */
   OBSTACLE /**< Point contains an obstacle and cannot be accessed */
};

#endif // H_OCCUPANCY_H