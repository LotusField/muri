#include "grid.h"
#include <Eigen/Dense>
#include <algorithm>

Grid::Grid() {}

Grid::Grid(Gridcoords gridcoords)
: gridcoords(gridcoords)
{
    for(std::size_t dim = 0; dim < gridcoords.size(); dim++)
    {
        if (!std::is_sorted(gridcoords[dim].cbegin(), gridcoords[dim].cend())) // if not sorted
        {
            std::sort(this->gridcoords[dim].begin(), this->gridcoords[dim].end()); // sorts coordinates of the grid along dimension dim
        }
    }
}

Id Grid::id(const Idvec& idvec) const
{
    return idvec[2]*gridcoords[0].size()*gridcoords[1].size()
           +idvec[1]*gridcoords[0].size()
           +idvec[0];
}

Id Grid::id(const Coordvec& coordvec) const
{
    return id(idvec(coordvec));
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

Idvec Grid::idvec(const Coordvec& coordvec) const
{
    for(std::size_t dim = 0; dim < gridcoords.size(); dim++)
    {
        std::find(gridcoords[dim].begin(), gridcoords[dim].end(), coordvec[dim]);
    }
    //std::find(gridcoords[dim].begin(), gridcoords[dim].end(), item);
    // to be written
}

Coordvec Grid::coordvec(Id id) const
{
    return coordvec(idvec(id));
}

Coordvec Grid::coordvec(const Idvec& idvec) const
{
    Coordvec coordvec;
    for(std::size_t dim = 0; dim < std::size(gridcoords); dim++)
    {
        coordvec[dim] = gridcoords[dim][idvec[dim]];
    }
    return coordvec;
}

Gridcoords Grid::getGridcoords() const
{
    return gridcoords;
}
