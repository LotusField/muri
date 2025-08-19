#ifndef GRID_H
#define GRID_H

#include "gvar.h"
#include <array>
#include <vector>
#include <Eigen/Dense>

using Coord = double;
using Gridcoords = std::array<std::vector<Coord>,g_ndim>;
using Id = std::size_t;
using Coordvec = Eigen::Vector<Coord, g_ndim>;
using Idvec = Eigen::Vector<Id, g_ndim>;

// typedef std::array<std::vector<double>,g_ndim> gridcoords;
// typedef Eigen::Vector<double, g_ndim> coordvec;
// typedef Eigen::Vector<std::size_t, g_ndim> idvec;

class Grid
{
public:
    Grid();

    Grid(Gridcoords gridcoords);

    // Convert indices along the different dimensions to the corresponding index
    Id id(const Idvec& idvec) const;

    // Convert indices along the different dimensions to the corresponding index
    Id id(const Coordvec& coordvec) const;

    // Convert an index to the corresponding indices along the different dimensions
    Idvec idvec(Id id) const;

    // Convert an index to the corresponding indices along the different dimensions
    Idvec idvec(const Coordvec& id) const;

    // Convert an index to the corresponding absolute coordinates
    Coordvec coordvec(Id id) const;

    // Convert indices along the corresponding different dimensions to the absolute coordinates
    Coordvec coordvec(const Idvec& vec) const;

    const Gridcoords& getGridcoords() const;

private:

    Gridcoords gridcoords;
};

#endif // GRID_H
