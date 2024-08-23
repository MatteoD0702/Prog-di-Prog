#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "person.hpp"
#include "desease.hpp"

#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>

#include <vector>
using std::vector;


class Population{

    int dimension;
    int day = 0;
    vector<vector<Person>> people;
    vector<vector<Person>> people_updated;
    Desease plague;

    public:

    /* richiama start per inizializzare Person in modo random e permette di inizializzare Desease tramite init_variables */
    void init_population(int dim, double starting_percentage, double inf, double dead, double heal, int imm_p);

    /*returna lo state dell'elemento i-j*/
    int GetElementState(int i, int j);

    /*returna se l'elemento i-j è il quarantena o meno*/
    bool GetElementQuarantine(int i, int j);

    /*prermette di gestire gli eventi definiti (Enter, Q, F) */
    void Event_Manager(sf::Event event);

    /*permette di copiare i cambiamenti da people_updated a people*/
    void Confirm();

    /*conta il numero di elementi che condividono lo stato "state" */
    double CountState(int state);

    /*returna i giorni dall'inizio della simulazione*/
    int GetDay();

    /*Generate_Text serve a creare una streamstring contenente i dati da proiettare a schermo*/
    std::stringstream Generate_Text();

};

#endif