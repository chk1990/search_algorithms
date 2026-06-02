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
   FREE = 0, /**< Point is free and can be accessed */
   OBSTACLE = 1, /**< Point contains an obstacle and cannot be accessed */
   PATH = 2, /**< Point belongs to a path */
   GOAL = 3 /**< Point is the goal */
};

#endif // H_OCCUPANCY_H