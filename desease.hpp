#ifndef DESEASE_HPP
#define DESEASE_HPP

#include <iostream>


class Desease{

    double infectivity;      //percentuale che ogni infetto ha di infettare un vicino (0-->1)
    double deadliness;       //percentuale che un malato diventi morto (1-->4)
    double heal_percentage;  //percentuale di guarire (1-->2)
    int immunity_period;     //tempo di immunità post-guarigione (2-->0)


    public: 

    //costruttore che usa 4 variabili per inizializzare la malattia

    //funzione per inizializzare i dati di Deasease
    void init_variables(double inf, double dead, double heal, int imm_p);

    //funzioni dedicate al passaggio delle variabili double
    int GetPeriod();

    double GetInfect();

    double GetHeal();

    double GetDeadly();

};

// sistemare la formattazione (max 72/76 colonne)... poulation va cambiato(metodi inclusivi per togliere gli if nidificati) Population class: con person e desease come elementi 

// metodi getter const e initvariables-> Setvariables, testcase, e altra roba

#endif