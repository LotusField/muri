#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "grid.h"
#include <vector>
#include <Eigen/Dense>

std::vector<Coord> ax1 = {1.1,2.2,3.3};
std::vector<Coord> ax2 = {11.1,22.2,33.3,44.4};
std::vector<Coord> ax3 = {111.1,222.2,333.3,444.4,555.5};
Gridcoords gridcoords = {ax1,ax2,ax3};
Grid grid(gridcoords);

Idvec iv0 = {0,0,0};
Idvec iv4 = {1,1,0};
Idvec iv9 = {0,3,0};
Idvec iv14 = {2,0,1};
Idvec iv19 = {1,2,1};

Coordvec cv0 = {1.1,11.1,111.1};
Coordvec cv4 = {2.2,22.2,111.1};
Coordvec cv9 = {1.1,44.4,111.1};
Coordvec cv14 = {3.3,11.1,222.2};
Coordvec cv19 = {2.2,33.3,222.2};

TEST_CASE( "Grid::id(const Idvec& idvec)", "[Grid::id]" ) {
    REQUIRE( grid.id(iv0) == 0);
    REQUIRE( grid.id(iv4) == 4);
    REQUIRE( grid.id(iv9) == 9);
    REQUIRE( grid.id(iv14) == 14);
    REQUIRE( grid.id(iv19) == 19);
    BENCHMARK("Grid::id 19") {
        return grid.id(iv19);
    };
}

TEST_CASE( "Grid::id(const Coordvec& coordvec)", "[Grid::id]" ) {
    REQUIRE( grid.id(cv0) == 0);
    REQUIRE( grid.id(cv4) == 4);
    REQUIRE( grid.id(cv9) == 9);
    REQUIRE( grid.id(cv14) == 14);
    REQUIRE( grid.id(cv19) == 19);
    BENCHMARK("Grid::id 19") {
        return grid.id(cv19);
    };
}

TEST_CASE( "Grid::idvec(Id id)", "[Grid::idvec]" ) {
    REQUIRE( grid.idvec(0) == iv0);
    REQUIRE( grid.idvec(4) == iv4);
    REQUIRE( grid.idvec(9) == iv9);
    REQUIRE( grid.idvec(14) == iv14);
    REQUIRE( grid.idvec(19) == iv19);
    BENCHMARK("Grid::idvec 19") {
        return grid.idvec(19);
    };
}

TEST_CASE( "Grid::idvec(const Coordvec& coordvec)", "[Grid::idvec]" ) {
    REQUIRE( grid.idvec(cv0) == iv0);
    REQUIRE( grid.idvec(cv4) == iv4);
    REQUIRE( grid.idvec(cv9) == iv9);
    REQUIRE( grid.idvec(cv14) == iv14);
    REQUIRE( grid.idvec(cv19) == iv19);
    BENCHMARK("Grid::idvec 19") {
        return grid.idvec(cv19);
    };
}

TEST_CASE( "Grid::coordvec(Id id)", "[Grid::coordvec]" ) {
    REQUIRE( grid.coordvec(0) == cv0);
    REQUIRE( grid.coordvec(4) == cv4);
    REQUIRE( grid.coordvec(9) == cv9);
    REQUIRE( grid.coordvec(14) == cv14);
    REQUIRE( grid.coordvec(19) == cv19);
    BENCHMARK("Grid::coordvec 19") {
        return grid.coordvec(19);
    };
}

TEST_CASE( "Grid::coordvec(const Idvec& idvec)", "[Grid::coordvec]" ) {
    REQUIRE( grid.coordvec(iv0) == cv0);
    REQUIRE( grid.coordvec(iv4) == cv4);
    REQUIRE( grid.coordvec(iv9) == cv9);
    REQUIRE( grid.coordvec(iv14) == cv14);
    REQUIRE( grid.coordvec(iv19) == cv19);
    BENCHMARK("Grid::coordvec 19") {
        return grid.coordvec(iv19);
    };
}
