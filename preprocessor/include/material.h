#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>


enum Symmetry {ISOTROPIC,CARTESIAN,CYLINDRICAL};

class Material
{
public:

    Material();

    //! Material constructor
    /*!
    Takes information on the material properties useful for static hygrothermal diffusion.
    This constructor assumes that the material is isotropic.
        \param label name of the material/product.
        \param lambda linear conducitivty in [W/m K].
        \param delta linear vapour diffusion coefficient in [mg/h m Pa].
    */
    Material(std::string label, double lambda, double delta);

    //! Material constructor
    /*!
    Takes information on the material properties useful for static hygrothermal diffusion.
        \param label name of the material/product.
        \param lambda linear conducitivty in [W/m K].
        \param lambdaSymmetry either ISOTROPIC, CARTESIAN, or CYLINDRICAL (enumy type Symmetry).
        \param delta linear vapour diffusion coefficient in [mg/h m Pa].

    */
    Material(std::string label, double lambda, Symmetry lambdaSymmetry, double delta, Symmetry deltaSymmetry);

    //! label get method
    /*!
    Gets the label/name of the material.
        \return label the label/name of the material.
    */
    std::string getLabel() const;

    //! lambda get method
    /*!
    Gets the thermal conductivity coefficient of the material.
        \return the thermal conductivity coefficient (lambda)
    */
    double getLambda() const;

    //! lambda symmetry get method
    /*!
    Gets the thermal diffusion symmetry of the medium.
        \return the vapour diffusion symmetry of the medium.
    */
    Symmetry getLambdaSymmetry() const;

    //! delta get method
    /*!
    Gets the vapour diffusion coefficient of the material.
        \return the vapour diffusion coefficient (delta)
    */
    double getDelta() const;

    //! delta symmetry get method
    /*!
    Gets the vapour diffusion symmetry of the medium.
        \return the vapour diffusion symmetry of the medium.
    */
    Symmetry getDeltaSymmetry() const;

private:

    std::string label;

    double lambda;
    Symmetry lambdaSymmetry;

    double delta;
    Symmetry deltaSymmetry;
};

#endif // MATERIAL_H
