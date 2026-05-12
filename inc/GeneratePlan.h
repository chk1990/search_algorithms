/**
 * @file GeneratePlan.h
 * @author Christoph Kolhoff
 */

#ifndef H_GENERATE_PLAN_H
#define H_GENERATE_PLAN_H

#include<iostream>
#include<memory>
#include<string>
#include<vector>

#include "Grid2D.h"

/**
 * @class GeneratePlan
 * @brief Prints all the plans to test
 *      A plan consists of multiple points that 
 */
class GeneratePlan {
    public:
        GeneratePlan();
        
        void printPlan2D(const size_t ind, const std::string fileName) const;

    private:
        std::unique_ptr<Grid2D> plan; /**< All information of the map */

        void printPlan2D1(const std::string fileName) const;
};

#endif // H_GENERATE_PLAN_H