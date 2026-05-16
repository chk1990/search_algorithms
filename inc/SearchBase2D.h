/**
 * @file SearchBase.h
 * @author Christoph Kolhoff
 */

#ifndef H_SEARCH_BASE_H
#define H_SEARCH_BASE_H

#include<string>

#include "Grid2D.h"

template<typename T>
class SearchBase2D {
    private:
        std::unique_ptr<Grid2D<T>> grid;
    
    public:
        SearchBase2D(const std::string filename);
        ~SearchBase2D() {};        
};

template class SearchBase2D<int>;
template class SearchBase2D<float>;
template class SearchBase2D<double>;

#endif // H_SEARCH_BASE_H