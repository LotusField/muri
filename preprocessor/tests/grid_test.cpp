#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "grid.h"
#include <vector>
#include <Eigen/Dense>

std::vector<Coord> v = {2.2,1.1,3.3};
Gridcoords gridcoords = {v,v,v};
Grid grid(gridcoords);

TEST_CASE( "Grid::idvec(Id id)", "[Grid::idvec]" ) {
    Idvec v0 = {0,0,0};
    Idvec v4 = {1,1,0};
    Idvec v9 = {0,0,1};
    Idvec v14 = {2,1,1};
    Idvec v19 = {1,0,2};

    REQUIRE( grid.idvec(0) == v0);
    REQUIRE( grid.idvec(4) == v4);
    REQUIRE( grid.idvec(9) == v9);
    REQUIRE( grid.idvec(14) == v14);
    REQUIRE( grid.idvec(19) == v19);
    BENCHMARK("Grid::idvec 19") {
        return grid.idvec(19);
    };
}

TEST_CASE( "Grid::coordvec(Id id)", "[Grid::coordvec]" ) {
    Coordvec c0 = {1.1,1.1,1.1};
    Coordvec c4 = {2.2,2.2,1.1};
    Coordvec c9 = {1.1,1.1,2.2};
    Coordvec c14 = {3.3,2.2,2.2};
    Coordvec c19 = {2.2,1.1,3.3};

    REQUIRE( grid.coordvec(0) == c0);
    REQUIRE( grid.coordvec(4) == c4);
    REQUIRE( grid.coordvec(9) == c9);
    REQUIRE( grid.coordvec(14) == c14);
    REQUIRE( grid.coordvec(19) == c19);
    BENCHMARK("Grid::coordvec 19") {
        return grid.idvec(19);
    };
}
