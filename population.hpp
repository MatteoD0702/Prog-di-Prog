#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <iomanip>
#include <sstream>
#include <vector>

#include "desease.hpp"
#include "person.hpp"
using std::vector;

class Population {
  int m_dimension;
  int m_day = 0;
  vector<vector<Person>> m_people;
  vector<vector<Person>> m_people_updated;
  Desease m_plague;

 public:
  /* richiama start per inizializzare Person in modo random e permette di
   * inizializzare Desease tramite init_variables */
  void initPopulation(int dim, double starting_percentage, double inf,
                      double dead, double heal, int imm_p);

  /*returna lo state dell'elemento i-j*/
  int getElementState(int i, int j) const;

  /*returna se l'elemento i-j è il quarantena o meno*/
  bool getElementQuarantine(int i, int j) const;

  /*controlla i vicini di una cella sana*/
  void updateHealthy(int i, int j);

  /*aggiorna la quarantena delle celle*/
  void updateQuarantine();

  /*scorre l'array richiamando i metodi di evoluzione*/
  void evolve();

  /*permette di copiare i cambiamenti da people_updated a people*/
  void saveUpdates();

  /*conta il numero di elementi che condividono lo stato "state" */
  double countState(int state);

  /*returna i giorni dall'inizio della simulazione*/
  int getDay() const;

  /*Generate_Text serve a creare una streamstring contenente i dati da
   * proiettare a schermo*/
  std::stringstream generateText();

  /*elimina tutti gli oggetti istanziati nei vettori*/
  void clearPopulation();
};

#endif