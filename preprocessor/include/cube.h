#ifndef CUBE_H
#define CUBE_H

#include "gvar.h"
#include "grid.h"
#include <array>
#include "material.h"

using Coordrange = std::array<Coord,2>;

class Cube
{
public:

    Cube();

    //! Cube constructor
    /*!
    Takes information on the cube location as parameters.
        \param mincorner the corner location with the minimal x, y and z.
        \param maxcorner the corner location with the maximal x, y and z.
    */
    Cube(const Coordvec& mincorner, const Coordvec& maxcorner);

    //! Cube constructor
    /*!
    Takes information on the cube location as parameters.
        \param ranges an array containing the ranges for each dimension of the cube.
    */
    Cube(const std::array<Coordrange, g_ndim>& ranges);

    //! ranges get method
    /*!
    Get informations on the cube location and dimensions in space.
        \return a vector containing the ranges spanned by each dimension of the cube.
    */
    std::array<Coordrange, g_ndim> getRanges(); const

    //! material get method
    /*!
    Get informations the material associated to the cube.
        \return an object describing the material associated to the cube.
    */
    Material getMaterial(); const

    //! show get method
    /*!
    Whether the cube has to be shown in the 3D gui.
        \return a boolean whether the cube has to be shown in the 3D gui.
    */
    void getShow(); const

private:

    std::array<Coordrange, g_ndim> ranges;
    Material material;
    bool show = true;
};

#endif // CUBE_H
