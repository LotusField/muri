#ifndef GRID_H
#define GRID_H

#include "gvar.h"
#include <array>
#include <vector>

class Grid
{
public:
    Grid();

private:
    std::array<std::vector<double>,g_ndim> coord;
};

#endif // GRID_H
