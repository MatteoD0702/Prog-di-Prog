#include "person.hpp"


void Person::SetState(int st)
{
    state=st;
}

void Person::SetQuarantine(bool qrnt)
{
    quarantine=qrnt;
}

void Person::SetImmu_Time(int imm_t)
{
    immunity_time=imm_t;
}

void Person::init_variables(int st, bool qrnt, int imm_t)
{
    SetState(st);
    SetQuarantine(qrnt);
    SetImmu_Time(imm_t);
}

void Person::init_variables(Person old_person)
{
    SetState(old_person.GetState());
    SetQuarantine(old_person.GetQuarantine());
    SetImmu_Time(old_person.GetImmu_Time());
}

void Person::start(double starting_percentage)
{
    int roll = rand()%100;
    if(roll < starting_percentage){SetState(1);}
    else{SetState(0);}
}

int Person::GetState()
{
    return state;
}

bool Person::GetQuarantine()
{
    return quarantine;
}

int Person::GetImmu_Time()
{
    return immunity_time;
}

void Person::immunity_check(int time, int period)
{
    if (time < period){immunity_time++;} //la cella rimane immune
    else {immunity_time = 0; SetState(0);} // la cella torna infettabile
}

void Person::destiny(double dead, double heal)
{
    if(rand()%100 < dead){
        SetState(4); //la cella è morta
        quarantine=0;
    }
    else{
        if(rand()%100 < heal){
            SetState(2); //la cella è guarita
            quarantine=0;
        }
    }
    
}

void Person::infection(double infectivity)
{
    int roll = rand()%100;
    if(roll < infectivity){SetState(1);}
}

