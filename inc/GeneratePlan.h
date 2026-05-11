/**
 * @file GeneratePlan.h
 * @author Christoph Kolhoff
 */

#ifndef H_GENERATE_PLAN_H
#define H_GENERATE_PLAN_H

#include<string>

/**
 * @brief Prints all the plans to test
 * @class GeneratePlan
 */
class GeneratePlan {
    public:
        GeneratePlan();
        void printPlan(size_t ind, std::string fileName);

    private:
        void printPlan1(std::string fileName);
};

#endif // H_GENERATE_PLAN_H