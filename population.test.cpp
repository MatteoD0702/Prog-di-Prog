#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "population.cpp"

#include "doctest.h"

// g++ -o test.out population.test.cpp

TEST_CASE("Testing init_population") {

  SUBCASE("certezza di nascere malato") {
    int count=0;

    Population world;
    world.init_population(100, 100, 0, 0, 0, 0);

    for(int i=1; i<101; i++){
        for(int j=1; j<101; j++){
            if(world.GetElementState(i,j) != 1){count++;}
        }
    }

    CHECK(count == 0);
  }

  SUBCASE("certezza di nascere sano") {
    int count=0;

    Population world;
    world.init_population(100, 0, 0, 0, 0, 0);

    for(int i=1; i<101; i++){
        for(int j=1; j<101; j++){
            if(world.GetElementState(i,j) != 0){count++;}
        }
    }

    CHECK(count == 0);
  }

}