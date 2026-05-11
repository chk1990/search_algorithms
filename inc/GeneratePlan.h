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

#include "Point2D.h"

/**
 * @brief Prints all the plans to test
 * @class GeneratePlan
 */
class GeneratePlan {
    public:
        GeneratePlan();
        void printPlan(const size_t ind, const std::string fileName) const;

    private:
        std::unique_ptr<std::vector<Point2D>> plan;
        void printPlan1(const std::string fileName) const;
};

#endif // H_GENERATE_PLAN_H