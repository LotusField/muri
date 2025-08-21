#ifndef MODEL_H
#define MODEL_H

#include "cube.h"

class Model
{
public:

    Model();

    //! Model constructor
    /*!
    Takes a ___ .
        \param .
        \param .
    */

    void addCube(Cube cube);

    void refreshGrid();

private:

    std::vector<Cube> cubeList;
    Grid grid;
};

#endif // MODEL_H
