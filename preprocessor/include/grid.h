#ifndef GRID_H
#define GRID_H

#include "gvar.h"
#include <array>
#include <vector>
#include <Eigen/Dense>

//! Coord type definition
/*! Used for scalars that represent an absolute scalar coordinate. */
using Coord = double;

//! Gridcoords type definition
/*! Used for variables that describe space gridding along each dimension of the numerical problem. */
using Gridcoords = std::array<std::vector<Coord>,g_ndim>;

//! Id type definition
/*! Used for scalars that represent a scalar index. Each point in space has a unique corresponding index. */
using Id = std::size_t;

//! Idvec type definition
/*! Used for vectors that represent the index along each dimension of a location in space. */
using Idvec = Eigen::Vector<Id, g_ndim>;

//! Coordvec type definition
/*! Used for vectors that represent the coordinates along each dimension of a location in space. Those can be interpreted as the physical coordinates*/
using Coordvec = Eigen::Vector<Coord, g_ndim>;

//! Grid class
/*!
The attributes describe the gridding of the numerical problem to solve.
The methods allows for indices and coordinates transformations with respect to the grid.
 */
class Grid
{
public:

    Grid();

    //! Grid constructor
    /*!
    Takes a gridcoords variable that describes the gridding of the numerical problem.
    If the coordinates in gridcoords are not sorted for each dimensions, the constructor sorts them.
    */
    Grid(Gridcoords gridcoords);

    //! Convert indices along the different dimensions to the corresponding index.
    /*!
        \param idvec a constant reference of vector of indices.
        \return the corresponding id.
    */
    Id id(const Idvec& idvec) const;

    //! Convert coordinates along the different dimensions to the corresponding index.
    /*!
        \param coordvec a constant reference of vector of coordinates.
        \return the corresponding id.
    */
    Id id(const Coordvec& coordvec) const;

    //! Convert an index to the corresponding indices along the different dimensions.
    /*!
        \param id index.
        \return the corresponding vector of indices.
    */
    Idvec idvec(Id id) const;

    //! Convert an index to the corresponding indices along the different dimensions.
    /*!
        \param coordvec a constant reference of vector of coordinates.
        \return the corresponding vector of indices.
    */
    Idvec idvec(const Coordvec& id) const;

    //! Convert an index to the corresponding absolute coordinates.
    /*!
        \param id index.
        \return the corresponding vector of coordinates.
    */
    Coordvec coordvec(Id id) const;

    //! Convert indices along the corresponding different dimensions to the absolute coordinates.
    /*!
        \param coordvec a constant reference of vector of coordinates.
        \return the corresponding vector of coordinates.
    */
    Coordvec coordvec(const Idvec& vec) const;

    //! Get function for the gridcoords variable describing the gridding of the numerical problem.
    /*!
        \return a constant reference on the grid coordinates
    */
    const Gridcoords& getGridcoords() const;

private:

    Gridcoords gridcoords;
};

#endif // GRID_H
