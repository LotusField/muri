#ifndef GRID_H
#define GRID_H

#include "gvar.h"
#include <array>
#include <vector>
#include <Eigen/Dense>

using Gridcoords = std::array<std::vector<double>,g_ndim>;
using Id = std::size_t;
using Coordvec = Eigen::Vector<double, g_ndim>;
using Idvec = Eigen::Vector<Id, g_ndim>;

// typedef std::array<std::vector<double>,g_ndim> gridcoords;
// typedef Eigen::Vector<double, g_ndim> coordvec;
// typedef Eigen::Vector<std::size_t, g_ndim> idvec;

class Grid
{
public:
    Grid();

    Grid(Gridcoords gridcoords);

    // Convert indices along the different dimension to the absolute coordinates
    Coordvec coordvec(const Idvec& vec) const;

    // Convert an index to the indices along the different dimension
    Idvec idvec(Id id) const;



    Gridcoords getGridcoords() const;

private:

    Gridcoords gridcoords;
};

#endif // GRID_H
