#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include "grid.h"
#include <vector>
#include <Eigen/Dense>

std::vector<double> v = {1,2,3};
Gridcoords gridcoords = {v,v,v};
Grid grid(gridcoords);
Id id(20);

Eigen::Vector<Id,3> v0 = {0,0,0};
Eigen::Vector<Id,3> v4 = {1,1,0};
Eigen::Vector<Id,3> v9 = {0,0,1};
Eigen::Vector<Id,3> v14 = {2,1,1};
Eigen::Vector<Id,3> v19 = {1,0,2};

TEST_CASE( "Grid::idvec(Id id)", "[Grid::idvec]" ) {
    REQUIRE( grid.idvec(0) == v0);
    REQUIRE( grid.idvec(4) == v4);
    REQUIRE( grid.idvec(9) == v9);
    REQUIRE( grid.idvec(14) == v14);
    REQUIRE( grid.idvec(19) == v19);
}
