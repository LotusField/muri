#ifndef GVAR_H
#define GVAR_H

#include <cstddef> // for std::size_t

//

//! Global variable for problem number of dimensions.
/*! Number of geometrical dimensions of the problem. */
constexpr std::size_t g_ndim(3);

//! Global variable for problem maximal number of dimensions.
/*! Number of geometrical dimensions of the problem. */
constexpr std::size_t g_maxdim(3);

#endif // GVAR_H
