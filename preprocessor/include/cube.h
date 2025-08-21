#ifndef CUBE_H
#define CUBE_H

#include "gvar.h"
#include "grid.h" # to remove and put type definition elsewhere
#include <array>
#include <vector>

using Coordrange = std::array<Coord,2>;

class Cube
{
public:

    Cube();

    //! Cube constructor
    /*!
    Takes a ___ variable that describes the spatial location of the cube.
        \param mincorner the corner location with the minimal x, y and z.
        \param maxcorner the corner location with the maximal x, y and z.
    */
    Cube(Coordvec mincorner, Coordvec maxcorner);

    Cube(std::array<Coordrange, g_ndim> ranges);

private:

    std::array<Coordrange, g_ndim> ranges;
    Material material;
    bool show = true;
};

#endif // CUBE_H
