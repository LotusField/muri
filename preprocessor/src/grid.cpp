#include "grid.h"
#include <Eigen/Dense>
#include <algorithm>
#include "gvar.h"

Grid::Grid() {}

Grid::Grid(Gridcoords gridcoords)
    : gridcoords(std::move(gridcoords))  // move to avoid unnecessary copy
{
    for (auto& coords : this->gridcoords)
    {
        if (!std::is_sorted(coords.begin(), coords.end()))
        {
            std::sort(coords.begin(), coords.end());
        }
    }
}

Id Grid::id(const Idvec& idvec) const // to generalise to dim <= 3
{
    const std::size_t size0 = gridcoords[0].size();
    const std::size_t size1 = gridcoords[1].size();

    const std::size_t stride2 = size0 * size1;  // stride for dim 2
    const std::size_t stride1 = size0;          // stride for dim 1

    return idvec[2] * stride2 + idvec[1] * stride1 + idvec[0];
}

Id Grid::id(const Coordvec& coordvec) const //to be optimised cause coordvec returns something that could be "not stored"
{
    return id(idvec(coordvec));
}

Idvec Grid::idvec(Id id) const
{
    std::array<std::size_t, g_maxdim> len{1,1,1};
    for(std::size_t dim = 0; dim < gridcoords.size(); dim++)
    {
        len[dim] = gridcoords[dim].size();
    }

    const std::size_t lenxy = len[0] * len[1];

    Id idz = id / lenxy;
    Id rem = id % lenxy;  // remainder after extracting z

    Id idy = rem / len[0];
    Id idx = rem % len[0];

    return Idvec{idx, idy, idz};
}

/* COULD BE GOOD, TO BE TESTED:
 * Idvec Grid::idvec(Id id) const
{
    const std::size_t dims = gridcoords.size();
    Idvec idvec(dims);
    std::vector<std::size_t> strides(dims, 1);

    // Compute strides (row-major order)
    for (std::size_t i = 1; i < dims; ++i)
        strides[i] = strides[i - 1] * gridcoords[i - 1].size();

    // Decode the flat ID into multi-dimensional index
    for (std::size_t dim = dims; dim-- > 0; )
    {
        idvec[dim] = id / strides[dim];
        id %= strides[dim];
    }

    return idvec;
}*/

Idvec Grid::idvec(const Coordvec& coordvec) const
{
    Idvec idvec(gridcoords.size());

    for (std::size_t dim = 0; dim < gridcoords.size(); ++dim)
    {
        const auto& gcAlongDim = gridcoords[dim];
        auto it = std::lower_bound(gcAlongDim.begin(), gcAlongDim.end(), coordvec[dim]);

        if (it == gcAlongDim.end() || *it != coordvec[dim]) {
            throw std::runtime_error("Coordinate not found in sorted grid dimension " + std::to_string(dim)); // to change to a try catch when snap to grid will be implemented
        }

        idvec[dim] = std::distance(gcAlongDim.begin(), it);
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
    Coordvec coordvec(dims);  // Allocate with correct size

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
