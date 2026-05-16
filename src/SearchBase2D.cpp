/**
 * @file SearchBase2D.cpp
 * @author Christoph Kolhoff
 */

#include "SearchBase2D.h"

SearchBase2D::SearchBase2D(const std::string filename)
{
    grid = std::make_unique<Grid2D<float>>();

    grid.get()->importPlanFile(filename);
    grid.get()->printContent();
}