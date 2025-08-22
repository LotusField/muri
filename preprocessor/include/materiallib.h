#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include <string>
#include <vector>
#include "material.h"


class MaterialLib
{
public:

    //! Material constructor
    /*!
    */
    MaterialLib();

    //! size of the library get method
    /*!
        \return the size of the available material library.
    */
    std::size_t getLibrarySize() const;

    //! specific material in the library get method
    /*!
     *  \param the index of the material to get.
        \return the material at the given index in the library.
    */
    std::size_t getMaterial(std::size_t index) const;

private:

    std::vector<Material> library;
};

#endif // MATERIALLIB_H
