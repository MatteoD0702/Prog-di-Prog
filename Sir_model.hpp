#ifndef SIR_MODEL_HPP
#define SIR_MODEL_HPP

#include "population.hpp"

#include <iostream>


class Sir_Model{

    double Beta;    //la probabilità di un sano di infettarsi
    double Gamma;   //la probabilità di un malato di essere rimosso
    int N;          //il numero totale di persone
    double S;          //il numero di sani
    double I;          //il numero di malati
    double R;          //il numero di rimossi

    public:

    //inizializza le variabili necessarie al modello SIR 
    Sir_Model(double infectivity, double deadliness, double heal_percentage, int n, int starting_S, int starting_I);

    //analysis permette di calcolare l'evoluzione del sistema a partire dalle equazioni del modello SIR
    void Analysis();

    //i metodi getter che restituiscono i dati
    int GetS();

    int GetI();

    int GetR();

    /*Generate_Text serve a creare una streamstring contenente i dati da proiettare a schermo*/
    std::stringstream Generate_Text();
};

#endif