#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>


enum Symmetry {ISOTROPIC,CARTESIAN,CYLINDRICAL};

class Material
{
public:

    Material();

    Material(string label, double lambda, double delta);

    //! Material constructor
    /*!
    ___
        \param ___
        \param ___
    */
    Material(string label, double lambda, double lambdaSymmetry, double delta, double deltaSymmetry);

    string getLabel() const;

    double getLambda() const;
    Symmetry getLambdaSymmetry() const;

    double getDelta() const;
    Symmetry getDeltaSymmetry() const;

private:

    string label;

    double lambda;
    Symmetry lambdaSymmetry;

    double delta;
    Symmetry deltaSymmetry;
};

#endif // MATERIAL_H
