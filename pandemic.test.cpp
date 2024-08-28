
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Sir_model.hpp"
#include "doctest.h"
#include "population.hpp"

/*
compila con:
g++ -o test.out pandemic.test.cpp Sir_model.cpp population.cpp person.cpp
desease.cpp esegui con:
./test.out
*/

/*
in questa sezione eseguiamo dei test sui metodi creati durante la scrittura del
codice. se in seguito ad una modifica di un metodo uno di questi test dovesse
fallire il metodo non funziona come dovrebbe.
*/

// ho fatto un solo test_file per population e SirModel.

// testiamo i metodi di SirModel

TEST_CASE("Testing analysis") {
  SUBCASE("analisi con zero infetti") {
    SirModel data(100, 100, 100, 10, 100, 0);
    data.analyse();

    CHECK(data.getS() == 100);
    CHECK(data.getI() == 0);
    CHECK(data.getR() == 0);
  }

  SUBCASE("analisi con mortalità/guarigione nulla") {
    SirModel data(0, 0, 0, 10, 0, 100);
    data.analyse();

    CHECK(data.getS() == 0);
    CHECK(data.getI() == 100);
    CHECK(data.getR() == 0);
  }

  SUBCASE("analisi con mortalità massima") {
    SirModel data(0, 100, 0, 10, 0, 100);
    data.analyse();

    CHECK(data.getS() == 0);
    CHECK(data.getI() == 0);
    CHECK(data.getR() == 100);
  }

  SUBCASE("analisi con guarigione massima") {
    SirModel data(0, 0, 100, 10, 0, 100);
    data.analyse();

    CHECK(data.getS() == 0);
    CHECK(data.getI() == 0);
    CHECK(data.getR() == 100);
  }

  SUBCASE("test del SIR con dati (1)") {
    SirModel data(10, 10, 10, 10, 90, 10);
    data.analyse();

    // fai i calcoli con la calcolatrice

    CHECK(data.getS() == 89.1);
    CHECK(data.getI() == 9);
    CHECK(data.getR() == 1.9);
  }

  SUBCASE("test del SIR con dati (2)") {
    SirModel data(50, 50, 50, 10, 50, 50);
    data.analyse();

    // fai i calcoli con la calcolatrice

    CHECK(data.getS() == 37.5);
    CHECK(data.getI() == 25);
    CHECK(data.getR() == 37.5);
  }
}
// finisce il testing di SirModel

// desease non ha bisogno di test visto che tutti i suoi metodi sono
// getter/setter

// testiamo person
// contenendo metodi random è possibile testare solo i casi limite (100% e 0%)

TEST_CASE("Testing startRandomly") {
  SUBCASE("certezza di essere sano") {
    Person collection[100000];
    int count = 0;

    for (Person subject : collection) {
      subject.startRandomly(0);
      if (subject.getState() != 0) {
        count++;
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("certezza di essere malato") {
    Person collection[100000];
    int count = 0;

    for (Person subject : collection) {
      subject.startRandomly(100);
      if (subject.getState() != 1) {
        count++;
      }
    }
    CHECK(count == 0);
  }
}

TEST_CASE("Testing checkImmunity") {
  SUBCASE("tempo passato non sufficiente") {
    Person subject;
    subject.initVariables(2, 0, 5);
    subject.checkImmunity(subject.getImmu_Time(), 10);

    CHECK(subject.getState() == 2);
    CHECK(subject.getImmu_Time() == 6);
  }

  SUBCASE("tempo passato sufficiente") {
    Person subject;
    subject.initVariables(2, 0, 5);
    subject.checkImmunity(subject.getImmu_Time(), 0);

    CHECK(subject.getState() == 0);
    CHECK(subject.getImmu_Time() == 0);
  }
}

TEST_CASE("Testing checkDestiny") {
  SUBCASE("certezza di morire") {
    Person subject;
    subject.initVariables(1, 1, 5);
    subject.checkDestiny(100, 0, 0);

    CHECK(subject.getState() == 4);
    CHECK(subject.getQuarantine() == 0);
  }

  SUBCASE("certezza di guarire") {
    Person subject;
    subject.initVariables(1, 1, 5);
    subject.checkDestiny(0, 100, 10);

    CHECK(subject.getState() == 2);
    CHECK(subject.getQuarantine() == 0);
  }

  SUBCASE("certezza di tornare sano") {
    Person subject;
    subject.initVariables(1, 1, 5);
    subject.checkDestiny(0, 100, 0);

    CHECK(subject.getState() == 0);
    CHECK(subject.getQuarantine() == 0);
  }
}

TEST_CASE("Testing infect") {
  SUBCASE("certezza di essere infettato") {
    Person subject;
    subject.initVariables(0, 0, 5);
    subject.infect(100);

    CHECK(subject.getState() == 1);
  }

  SUBCASE("certezza di non essere infettato") {
    Person subject;
    subject.initVariables(0, 0, 5);
    subject.infect(0);

    CHECK(subject.getState() == 0);
  }
}
// finisce il testing di person

// testiamo population

TEST_CASE("Testing initPopulation") {
  SUBCASE("corretta costruzione di una cornice sana") {
    Population world;
    world.initPopulation(100, 100, 0, 0, 0, 0);
    int count = 0;

    for (int i = 0; i < 102; i++) {
      for (int j = 0; j < 102; j++) {
        if (i == 0 or i == 101 or j == 0 or j == 101) {
          if (world.getElementState(i, j) != 0) {
            count++;
          }
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("popolazione completamente sana") {
    Population world;
    world.initPopulation(100, 0, 0, 0, 0, 0);
    int count = 0;

    for (int i = 1; i < 101; i++) {
      for (int j = 1; j < 101; j++) {
        if (world.getElementState(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("popolazione completamente malata") {
    Population world;
    world.initPopulation(100, 100, 0, 0, 0, 0);
    int count = 0;

    for (int i = 1; i < 101; i++) {
      for (int j = 1; j < 101; j++) {
        if (world.getElementState(i, j) != 1) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }
}

TEST_CASE("Testing updateQuarantine") {
  SUBCASE("quarantena disattivata di default") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 0, 0);
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementQuarantine(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("quarantena correttamente attivata(caso malati)") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 0, 0);
    world.updateQuarantine();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementQuarantine(i, j) != 1) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("quarantena correttamente attivata(caso sani)") {
    Population world;
    world.initPopulation(10, 0, 0, 0, 0, 0);
    world.updateQuarantine();
    world.saveUpdates();

    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementQuarantine(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("quarantena correttamente disattivata") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 0, 0);
    world.updateQuarantine();
    world.saveUpdates();
    world.updateQuarantine();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementQuarantine(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }
}

TEST_CASE("Testing evolve") {
  SUBCASE("controllo che la cornice non evolva") {
    Population world;
    world.initPopulation(10, 100, 100, 0, 0, 5);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (i == 0 or i == 11 or j == 0 or j == 11) {
          if (world.getElementState(i, j) != 0) {
            count++;
          }
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("evoluzione da sani a sani") {
    Population world;
    world.initPopulation(10, 0, 100, 0, 0, 5);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementState(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("evoluzione da malati a malati") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 0, 5);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementState(i, j) != 1) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("evoluzione da malati a morti") {
    Population world;
    world.initPopulation(10, 100, 0, 100, 0, 5);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementState(i, j) != 4) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("evoluzione da malati a guariti") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 100, 5);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementState(i, j) != 2) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }

  SUBCASE("evoluzione da malati a sani") {
    Population world;
    world.initPopulation(10, 100, 0, 0, 100, 0);
    world.evolve();
    world.saveUpdates();
    int count = 0;

    for (int i = 1; i < 11; i++) {
      for (int j = 1; j < 11; j++) {
        if (world.getElementState(i, j) != 0) {
          count++;
        }
      }
    }
    CHECK(count == 0);
  }
}
