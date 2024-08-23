#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>


class Person{

    int state=0;          /* stato 0: sano , stato 1: infetto , stato 2: guarito , stato 3:vaccinato , stato 4: morto */
    bool quarantine=0;    //1: in quarantena    0: libero
    int immunity_time=0;  //conto dei giorni di immunità post-guarigione

    public:

    //le varie funzioni per la modifica dei dati
    void SetState(int st);
    void SetQuarantine(bool qrnt);
    void SetImmu_Time(int imm_t);

    //init viene usata per inizializare un'entità a partire dai dati in input
    void init_variables(int st, bool qrnt, int imm_t);

    //un overload di init_variables che permette di assegnare a una persona i valori di un'altra
    void init_variables(Person old_person);

    //start deve inizializzare state in modo random
    void start(double starting_percentage);

    //le varie funzioni per restituire i dati private
    int GetState();
    bool GetQuarantine();
    int GetImmu_Time();

    // immunity_check confronta il tempo passato e quello impostato dall'utente
    void immunity_check(int time, int period);

    //destiny gestisce la morte o la guarigione di una cella malata
    void destiny(double dead, double heal);

    //infection prende in input una cella e le 8 celle attorno e verifica se la cella centrale si infetta
    void infection(double infectivit);

};

// modifica i dati in input di tutte le variabili anche nell'hpp se no nel cpp non vanno

#endif