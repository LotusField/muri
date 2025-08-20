#include "grid.h"
#include <Eigen/Dense>
#include <algorithm>
#include "gvar.h"

Grid::Grid() {}

Grid::Grid(Gridcoords gridcoords)
    : gridcoords(std::move(gridcoords))  // move to avoid unnecessary copy
{
    for (auto& axcoords : this->gridcoords)
    {
        if (!std::is_sorted(axcoords.cbegin(), axcoords.cend()))
        {
            std::sort(axcoords.begin(), axcoords.end());
        }
    }
}

Id Grid::id(const Idvec& idvec) const
{
    // x-dim is guaranteed (y and z not necessarily)
    const std::size_t lenx = gridcoords[0].size();
    const std::size_t leny = (gridcoords.size() > 1) ? gridcoords[1].size() : 1;

    const std::size_t lenxy = lenx * leny;

    const Id idz = (idvec.size() > 2) ? idvec[2] : 0;
    const Id idy = (idvec.size() > 1) ? idvec[1] : 0;
    const Id idx = idvec[0];

    return idz * lenxy + idy * lenx + idx;
}


Id Grid::id(const Coordvec& coordvec) const //maybe to be optimised because coordvec returns something in the stack which could be avoided
{
    return id(idvec(coordvec));
}

Idvec Grid::idvec(Id id) const
{
    const std::size_t lenx = gridcoords[0].size(); // x-dimension is guaranteed in all executions (at least 1 dimension to the problem)
    const std::size_t leny = (gridcoords.size() > 1) ? gridcoords[1].size() : 1; // if the problem has no y dimension, its length is 1 (hyperplanar)

    const std::size_t lenxy = lenx * leny; // number of element in each xy plane

    const Id idz = id / lenxy;
    const Id rem = id % lenxy;  // remainder after extracting z

    const Id idy = rem / lenx;
    const Id idx = rem % lenx;

    return Idvec{idx, idy, idz};
}

Idvec Grid::idvec(const Coordvec& coordvec) const
{
    Idvec idvec;

    for (std::size_t dim = 0; dim < gridcoords.size(); ++dim)
    {
        const std::vector<Coord>& axcoords = gridcoords[dim];
        auto it = std::lower_bound(axcoords.cbegin(), axcoords.cend(), coordvec[dim]);

        if (it == axcoords.cend() || *it != coordvec[dim]) {
            throw std::runtime_error("Coordinate not found in sorted grid dimension " + std::to_string(dim)); // to change to a try catch when snap to grid will be implemented. maybe the user will need to snap first
        }

        idvec[dim] = std::distance(axcoords.cbegin(), it);
    }

    return idvec;
}

Coordvec Grid::coordvec(Id id) const //to be optimised cause coordvec returns something that could be "not stored"
{
    return coordvec(idvec(id));
}

Coordvec Grid::coordvec(const Idvec& idvec) const
{
    const std::size_t dims = gridcoords.size();
    Coordvec coordvec;

    for (std::size_t dim = 0; dim < dims; ++dim)
    {
        coordvec[dim] = gridcoords[dim][idvec[dim]];
    }

    return coordvec;
}

const Gridcoords& Grid::getGridcoords() const
{
    return gridcoords;
}
