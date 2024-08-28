#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <random>

class Person {
  int m_state = 0; /* stato 0: sano , stato 1: infetto , stato 2: guarito ,
             stato 3:vaccinato(alla fine non implementato) , stato 4: morto */
  bool m_quarantine = 0;    // 1(true): in quarantena    0(false): libero
  int m_immunity_time = 0;  // conto dei giorni di immunità post-guarigione

 public:
  // le varie funzioni per la modifica dei dati
  void setState(int state);
  void setQuarantine(bool quarantine);
  void setImmunityTime(int immunity_time);

  // init viene usata per inizializare un'entità a partire dai dati in input
  void initVariables(int state, bool quarantine, int immunity_time);

  // un overload di init_variables che permette di assegnare a una persona i
  // valori di un'altra
  void initVariables(const Person& old_person);

  // start deve inizializzare state in modo random (numero da 0 a 99 contro la
  // percentuale)
  void startRandomly(double starting_percentage);

  // le varie funzioni per restituire i dati privati
  int getState() const;
  bool getQuarantine() const;
  int getImmu_Time() const;

  // immunity_check confronta il tempo passato e quello impostato dall'utente
  void checkImmunity(int time, int period);

  // destiny gestisce la morte o la guarigione di una cella malata
  void checkDestiny(double dead, double heal, int period);

  // infect verifica se la cella centrale si infetta (viene richiamato se i
  // vicini sono infetti)
  void infect(double infectivity);
};



#endif