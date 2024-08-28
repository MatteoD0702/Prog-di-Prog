#include "Sir_model.hpp"

SirModel::SirModel(double infectivity, double deadliness,
                   double heal_percentage, int n, int starting_S,
                   int starting_I) {
  // beta non è altro che la probabilità di infettarsi
  m_Beta = infectivity / 100;

  // gamma tiene in considerazione sia la morte che la guarigione
  m_Gamma = deadliness / 100 + (1 - deadliness / 100) * heal_percentage / 100;

  // il numero totale di persone è lo stesso delle celle della griglia
  m_N = n * n;

  // il numero di sani iniziale è dato dalla generazione random di world
  m_S = starting_S;

  // il numero di infetti non è altro che il numero di celle rosse all'inizio
  // della simulazione
  m_I = starting_I;

  // il numero di rimossi tiene conto dei guariti e dei morti(quindi all'inizio
  // sarà 0)
  m_R = 0;
}

void SirModel::update(double S, double I, double R) {
  m_S = S;
  m_I = I;
  m_R = R;
}

void SirModel::analyse() {
  // aggiorniamo i dati secondo il modello
  double S_updated = m_S - m_Beta * (m_S / m_N) * m_I;
  double I_updated = m_I + m_Beta * (m_S / m_N) * m_I - m_Gamma * m_I;
  double R_updated = m_R + m_Gamma * m_I;

  // li sostituiamo ai dati precedenti
  update(S_updated, I_updated, R_updated);
}

double SirModel::getS() const { return m_S; }

double SirModel::getI() const { return m_I; }

double SirModel::getR() const { return m_R; }

void SirModel::generateStandardOutput(int day) const {
  if (day == 0) {
    std::cout << std::fixed << std::setprecision(2)
              << "--------------------------------------\n"
              << "| giorno | sani | infetti | rimossi |\n"
              << "--------------------------------------\n";
  }

  std::cout << "|   " << day << "   | " << 100 * m_S / (m_N) << " |  "
            << 100 * m_I / (m_N) << "  |  " << 100 * m_R / (m_N) << "  |\n"
            << "-------------------------------------- \n";
}

std::stringstream SirModel::generateText() {
  std::stringstream text;
  text << std::fixed << std::setprecision(2) << "Previsione del Modello SIR: \n"
       << "Sani: " << 100 * m_S / (m_N) << "%\n"
       << "Infetti: " << 100 * m_I / (m_N) << "%\n"
       << "Rimossi: " << 100 * m_R / (m_N) << "%\n";
  return text;
}
