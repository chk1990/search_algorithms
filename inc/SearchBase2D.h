/**
 * @file SearchBase.h
 * @author Christoph Kolhoff
 */

#ifndef H_SEARCH_BASE_H
#define H_SEARCH_BASE_H

#include "Grid2D.h"

class SearchBase2D {
    private:
        std::unique_ptr<Grid2D<float>> grid;
    
    public:
        SearchBase2D();
};

#endif // H_SEARCH_BASE_H