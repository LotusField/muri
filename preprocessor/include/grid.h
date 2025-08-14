#ifndef GRID_H
#define GRID_H

#include "gvar.h"
#include <array>
#include <vector>

class Grid
{
public:
    Grid();

    // Convert indices along the different dimension to the absolute coordinates
    std::array<double, g_ndim> coords(const std::array<std::size_t, g_ndim>& vec, const std::array<std::vector<double>, g_ndim>& gridcoords) const;

    std::array<std::vector<double>,g_ndim> getGridcoords() const;

private:

    std::array<std::vector<double>,g_ndim> gridcoords;
};

#endif // GRID_H
