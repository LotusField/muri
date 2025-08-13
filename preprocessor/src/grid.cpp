#include "grid.h"

Grid::Grid() {}

std::array<double, g_ndim> Grid::coords(const std::array<std::size_t, g_ndim>& vec, const std::array<std::vector<double>, g_ndim>& gridcoords)
{
    std::array<double, g_ndim> coords;
    for(std::size_t dim = 0; dim < std::size(gridcoords); dim++)
    {
        coords[dim] = gridcoords[dim][vec[dim]];
    }
    return coords;
}

std::array<std::vector<double>,g_ndim> Grid::getGridcoords()
{
    return gridcoords;
}
