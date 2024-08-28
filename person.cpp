#include "person.hpp"

void Person::setState(int state) { m_state = state; }

void Person::setQuarantine(bool quarantine) { m_quarantine = quarantine; }

void Person::setImmunityTime(int immunity_time) {
  m_immunity_time = immunity_time;
}

void Person::initVariables(int state, bool quarantine, int immunity_t) {
  setState(state);
  setQuarantine(quarantine);
  setImmunityTime(immunity_t);
}

void Person::initVariables(const Person& old_person) {
  setState(old_person.getState());
  setQuarantine(old_person.getQuarantine());
  setImmunityTime(old_person.getImmu_Time());
}

void Person::startRandomly(double starting_percentage) {
  // routine di inizializzazione per le generazione di numeri casuali
  // ho usato random perchè sembra essere "più casuale" di rand()%100
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 99);

  if (distribution(gen) < starting_percentage) {
    setState(1);
  } else {
    setState(0);
  }
}

int Person::getState() const { return m_state; }

bool Person::getQuarantine() const { return m_quarantine; }

int Person::getImmu_Time() const { return m_immunity_time; }

void Person::checkImmunity(int time, int period) {
  if (time < period) {
    m_immunity_time++;
  }  // la cella rimane immune
  else {
    m_immunity_time = 0;
    setState(0);
  }  // la cella torna infettabile
}

void Person::checkDestiny(double dead, double heal, int period) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 99);

  if (distribution(gen) < dead) {
    setState(4);  // la cella è morta
    m_quarantine = 0;
  } else {
    if (distribution(gen) < heal) {
      if (period == 0) {
        setState(0);
      }  // non c'è periodo di immunità (la cella è sana)
      else {
        setState(2);
      }  // la cella è guarita
      m_quarantine = 0;
    }
  }
}

void Person::infect(double infectivity) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 99);

  if (distribution(gen) < infectivity) {
    setState(1);
  }
}
