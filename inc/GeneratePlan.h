/**
 * @file GeneratePlan.h
 * @author Christoph Kolhoff
 */

#ifndef H_GENERATE_PLAN_H
#define H_GENERATE_PLAN_H

#include<memory>
#include<string>
#include<vector>

#include "Grid2D.h"

/**
 * @class GeneratePlan
 * @brief Prints all the plans to test
 *        The type T can be int, float, double.
 */
template<typename T>
class GeneratePlan {
    public:
        GeneratePlan();
        
        void genPlan2D(const size_t ind, const std::string filename);

    private:
        std::unique_ptr<Grid2D<T>> plan; /**< All information of the map */

        void genPlan2D1(const std::string filename);
        void genPlan2D2(const std::string filename);
};

template class GeneratePlan<int>;
template class GeneratePlan<float>;
template class GeneratePlan<double>;

#endif // H_GENERATE_PLAN_H