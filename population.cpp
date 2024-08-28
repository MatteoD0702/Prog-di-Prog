#include "population.hpp"

void Population::initPopulation(int dim, double starting_percentage, double inf,
                                double dead, double heal, int imm_p) {
  m_dimension = dim;

  for (int i = 0; i < dim + 2; i++) {
    /* temporary_row conterrà gli state generati da start per ogni ciclo */
    vector<Person> temporary_row;

    for (int j = 0; j < dim + 2; j++) {
      /*
      la cornice sarà inizializzata come sana e non sarà mai più considerata,
      le altre celle invece saranno inizializzate casualmente secondo
      strating_percentage
      */
      Person temporary_element;
      if (i == 0 or i == dim + 1 or j == 0 or j == dim + 1) {
        temporary_element.startRandomly(0);
        temporary_row.push_back(temporary_element);
      } else {
        temporary_element.startRandomly(starting_percentage);
        temporary_row.push_back(temporary_element);
      }
    }
    m_people.push_back(temporary_row);
    m_people_updated.push_back(temporary_row);
  }

  /* inizializziamo la nostra malattia con init_variables di Desease */
  m_plague.initVariables(inf, dead, heal, imm_p);
}

int Population::getElementState(int i, int j) const {
  return m_people[i][j].getState();
}

bool Population::getElementQuarantine(int i, int j) const {
  return m_people[i][j].getQuarantine();
}

void Population::updateHealthy(int i, int j) {
  /*non c'è bisogno di escludere per k=i e z=j perchè siamo nel case in cui ij è
   * sana (non si può infettare da sola se è sana)*/
  for (int k = i - 1; k <= i + 1; k++) {
    for (int z = j - 1; z <= j + 1; z++) {
      if (m_people[k][z].getState() == 1 &&
          m_people[k][z].getQuarantine() == 0) {
        m_people_updated[i][j].infect(m_plague.getInfect());
      }
    }
  }
}

void Population::updateQuarantine() {
  for (int i = 1; i < m_dimension + 1; i++) {
    for (int j = 1; j < m_dimension + 1; j++) {
      if (m_people[i][j].getQuarantine() == 0 &&
          m_people[i][j].getState() == 1) {
        m_people_updated[i][j].setQuarantine(1);
      }

      if (m_people[i][j].getQuarantine() == 1) {
        m_people_updated[i][j].setQuarantine(0);
      }
    }
  }
}

void Population::evolve() {
  for (int i = 1; i < m_dimension + 1; i++) {
    for (int j = 1; j < m_dimension + 1; j++) {
      switch (m_people[i][j].getState()) {
        /*la cella è sana, può quindi essere infettata dai vicini tramite
         * infect,*/
        case 0:
          updateHealthy(i, j);
          break;

        /*la cella è malata, potrebbe morire o, nel caso non accadesse potrebbe
         * guarire*/
        case 1:
          m_people_updated[i][j].checkDestiny(
              m_plague.getDeadly(), m_plague.getHeal(), m_plague.getPeriod());
          break;

        case 2:  // la cella è guarita da poco, non può essere infettata.
                 // L'immunità è solo temporanea (se immunity_time <
                 // immunity_period)
          m_people_updated[i][j].checkImmunity(m_people[i][j].getImmu_Time(),
                                               m_plague.getPeriod());
          break;

        default:
          break;  // gli altri casi sono compresi in default (non evolvono)
      }
    }
  }
  m_day++;
}

void Population::saveUpdates() {
  for (int i = 1; i < m_dimension + 1; i++) {
    for (int j = 1; j < m_dimension + 1; j++) {
      m_people[i][j].initVariables(m_people_updated[i][j]);
    }
  }
}

double Population::countState(int state) {
  int count = 0;

  for (int i = 1; i < m_dimension + 1; i++) {
    for (int j = 1; j < m_dimension + 1; j++) {
      if (state == m_people[i][j].getState()) {
        count++;
      }
    }
  }

  return count;
}

int Population::getDay() const { return m_day; }

std::stringstream Population::generateText() {
  std::stringstream text;
  text << std::fixed << std::setprecision(2)
       << "Risultati della Simulazione: \n"
       << "Sani: "
       << 100 * (countState(0) + countState(2)) / (m_dimension * m_dimension)
       << "%\n"
       << "Infetti: " << 100 * countState(1) / (m_dimension * m_dimension)
       << "%\n"
       << "Rimossi: " << 100 * (countState(4)) / (m_dimension * m_dimension)
       << "%\n";
  return text;
}

void Population::clearPopulation() {
  m_people.clear();
  m_people_updated.clear();
}
