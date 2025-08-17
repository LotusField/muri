#include "grid.h"
#include <Eigen/Dense>

Grid::Grid() {}

Grid::Grid(Gridcoords gridcoords)
: gridcoords(gridcoords)
{}

Coordvec Grid::coordvec(const Idvec& idvec) const
{
    Coordvec coordvec;
    for(std::size_t dim = 0; dim < std::size(gridcoords); dim++)
    {
        coordvec[dim] = gridcoords[dim][idvec[dim]];
    }
    return coordvec;
}

Idvec Grid::idvec(Id id) const
{
    std::size_t lenx(gridcoords[1].size());
    std::size_t leny(gridcoords[2].size());
    Id idz(floor(id/(lenx*leny)));
    Id idy(floor((id-idz*lenx*leny)/lenx));
    Id idx(id-idy*lenx-idz*lenx*leny);
    Idvec idvec({idx,idy,idz});
    return idvec;
}

Gridcoords Grid::getGridcoords() const
{
    return gridcoords;
}
