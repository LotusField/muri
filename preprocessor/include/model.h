#ifndef MODEL_H
#define MODEL_H

#include "cube.h"

class Model
{
public:

    //! Model constructor
    /*!
    */
    Model();

    //! Add a cube to the model
    /*!
     * \param cube cube to be added to the model
    */
    void addCube(Cube cube);

    //! Refresh the grid to integrate eventual changes in the model
    /*!
    */
    void refreshGrid();

private:

    std::vector<Cube> cubeList;
    Grid grid;
};

#endif // MODEL_H
