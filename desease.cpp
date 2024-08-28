#include "desease.hpp"

void Desease::initVariables(double infectivity, double deadliness, double heal,
                            int imm_period) {
  m_infectivity = infectivity;
  m_deadliness = deadliness;
  m_heal_percentage = heal;
  m_immunity_period = imm_period;
}

int Desease::getPeriod() const { return m_immunity_period; }

double Desease::getInfect() const { return m_infectivity; }

double Desease::getHeal() const { return m_heal_percentage; }

double Desease::getDeadly() const { return m_deadliness; }
