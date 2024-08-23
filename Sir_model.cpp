#include "Sir_model.hpp"


Sir_Model::Sir_Model(double infectivity, double deadliness, double heal_percentage, int n, int starting_S, int starting_I)
{
    // beta non è altro che la probabilità di infettarsi
    Beta = infectivity/100;

    //gamma tiene in considerazione sia la morte che la guarigione
    Gamma = deadliness/100 + (1-deadliness/100)*heal_percentage/100;

    //il numero totale di persone è lo stesso delle celle della griglia
    N = n*n;

    //il numero di sani iniziale è dato dalla generazione random di world
    S = starting_S;

    //il numero di infetti non è altro che il numero di celle rosse all'inizio della simulazione
    I = starting_I;

    //il numero di rimossi tiene conto dei guariti e dei morti(quindi all'inizio sarà 0)
    R = 0;
}

void Sir_Model::Analysis()
{
    //aggiorniamo i dati secondo il modello
    double S_updated = S - Beta*(S/N)*I;
    double I_updated = I + Beta*(S/N)*I - Gamma*I;
    double R_updated = R + Gamma*I;

    //e li sostituiamo ai dati precedenti
    S = S_updated;
    I = I_updated;
    R = R_updated;
}

int Sir_Model::GetS()
{
    return S;
}

int Sir_Model::GetI()
{
    return I;
}

int Sir_Model::GetR()
{
    return R;
}

std::stringstream Sir_Model::Generate_Text()
{ 
    std::stringstream text;
    text<<std::fixed<<std::setprecision(2)
        <<"Previsione del Modello SIR: \n"
        <<"Sani: "<< 100*S/(N) <<"%\n"
        <<"Infetti: "<< 100*I/(N) <<"%\n"
        <<"Rimossi: "<< 100*R/(N) <<"%\n";
    return text;
}






