#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include <string>
#include <vector>
#include "material.h"


class MaterialLib
{
public:

    MaterialLib();

    Material();

    //! Material constructor
    /*!
    ___
        \param ___
        \param ___
    */

    std::sizte_t getLibrarySize() const;

    std::sizte_t getMaterial(std::size_t index) const;

private:

    std::vector<Material> library;
};

#endif // MATERIALLIB_H
