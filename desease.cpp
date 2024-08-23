#include "desease.hpp"


void Desease::init_variables(double inf, double dead, double heal, int imm_p)
{
    infectivity= inf; 
    deadliness= dead; 
    heal_percentage= heal; 
    immunity_period= imm_p;
}

int Desease::GetPeriod()
{
    return immunity_period;
}

double Desease::GetInfect()
{
    return infectivity;
}

double Desease::GetHeal()
{
    return heal_percentage;
}

double Desease::GetDeadly()
{
    return deadliness;
}
