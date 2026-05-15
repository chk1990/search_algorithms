/**
 * @file Occupancy.cpp
 * @author Christoph Kolhoff
 */

#include <iostream>

#include "Occupancy.h"

std::ostream& operator<<(std::ostream& os, const Occupancy oc) {
   switch (oc) {
      case FREE:
         os << " ";
         break;

      case OBSTACLE:
         os << "X";
         break;
      
      default:
         os << "!";
         break;
   }

   return os;
}