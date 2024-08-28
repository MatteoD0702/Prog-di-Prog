#ifndef DESEASE_HPP
#define DESEASE_HPP

#include <iostream>

class Desease {
  double m_infectivity;  // percentuale che ogni infetto ha di infettare un
                         // vicino (0-->1)
  double m_deadliness;       // percentuale che un malato diventi morto (1-->4)
  double m_heal_percentage;  // percentuale di guarire (1-->2)
  int m_immunity_period;     // tempo di immunità post-guarigione (2-->0)

 public:
  // funzione per inizializzare i dati di Deasease
  void initVariables(double infectivity, double deadliness, double heal,
                     int imm_period);

  // funzioni dedicate al passaggio delle variabili double
  int getPeriod() const;

  double getInfect() const;

  double getHeal() const;

  double getDeadly() const;
};



#endif