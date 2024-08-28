#ifndef SIR_MODEL_HPP
#define SIR_MODEL_HPP

#include <iomanip>
#include <iostream>
#include <sstream>

class SirModel {
  double m_Beta;   // la probabilità di un sano di infettarsi
  double m_Gamma;  // la probabilità di un malato di essere rimosso
  int m_N;         // il numero totale di persone (dim^2)
  double m_S;      // il numero di sani
  double m_I;      // il numero di malati
  double m_R;      // il numero di rimossi

 public:
  // inizializza le variabili necessarie al modello SIR
  SirModel(double infectivity, double deadliness, double heal_percentage, int n,
           int starting_S, int starting_I);

  // update permette di aggiornare i dati del SIR con quelli della simulazione
  void update(double S, double I, double R);

  // analysis permette di calcolare l'evoluzione del sistema a partire dalle
  // equazioni del modello SIR
  void analyse();

  // i metodi getter che restituiscono i dati
  double getS() const;

  double getI() const;

  double getR() const;

  void generateStandardOutput(int day) const;

  /*Generate_Text serve a creare una streamstring contenente i dati da
   * proiettare a schermo*/
  std::stringstream generateText();
};

#endif