#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>

#include "Sir_model.hpp"
#include "population.hpp"

/*
per compilare:
  g++ pandemic.cpp Sir_model.cpp population.cpp person.cpp desease.cpp
  -lsfml-graphics -lsfml-window -lsfml-system -Wall -Wextra -fsanitize=address
per eseguire:
  sudo ./a.out
*/
void eventManager(sf::Keyboard::Key key, Population& world, SirModel& data) {
  switch (key) {
    case sf::Keyboard::Enter:
      world.evolve();
      data.analyse();
      data.generateStandardOutput(world.getDay());
      break;

    case sf::Keyboard::Q:
      world.updateQuarantine();
      break;

    case sf::Keyboard::S:
      data.update(world.countState(0) + world.countState(2),
                  world.countState(1), world.countState(4));
      break;

    default:
      break;
  }
}

double Check_Percentage() {
  double perc;
  std::cin >> perc;

  if (perc < 0 or perc > 100) {
    std::cout << "percentuale non valida (i valori devono essere compresi tra "
                 "0 e 100), riprova:"
              << "\n";
    return Check_Percentage();
  }
  return perc;
}

int main() {
  // std::srand(static_cast<unsigned>(time(NULL)));
  // non più necessario dopo aver implementato <random>

  /*saranno la dimensione dell'array n*n e la probabilità di essere malato fin
   * dall'inizio*/
  int n;
  double starting_percentage;

  std::cout << "inserisci la dimensione della popolazione (il numero delle "
               "persone sarà n^2)"
            << "\n";
  std::cin >> n;
  while (n <= 0) {
    std::cout << "valore non valido (la dimensione deve essere maggiore di 0), "
                 "riprova:"
              << "\n";
    std::cin >> n;
  }
  std::cout << "inserisci la percentuale di popolazione già infetta (es. 10)"
            << "\n";
  starting_percentage = Check_Percentage();

  // le variabili utili a inizializzare la malattia
  double infect;
  double deadly;
  double heal;
  int immunity;

  std::cout << "inserisci il tasso di infezione, cioe' la probabilità che una "
               "persona infetti un vicino (es. 30)"
            << "\n";
  infect = Check_Percentage();
  std::cout << "inserisci il tasso di mortalità, cioe' la probabilità che una "
               "persona infetta muoia (es. 20)"
            << "\n";
  deadly = Check_Percentage();
  std::cout << "inserisci il tasso di guarigione, cioe'la probabilità che una "
               "persona infetta guarisca (es. 25)"
            << "\n";
  heal = Check_Percentage();
  std::cout << "inserisci il periodo di immunita' post-guarigione, cioè il "
               "numero di giorni di immunita' (es. 4)"
            << "\n";
  std::cin >> immunity;
  while (immunity < 0) {
    std::cout << "valore non valido (il numero di giorni deve essere maggiore "
                 "o uguale a zero), riprova:"
              << "\n";
    std::cin >> immunity;
  }

  Population world;
  world.initPopulation(n, starting_percentage, infect, deadly, heal, immunity);

  /*definiamo le specifiche della finestra*/
  unsigned const display_width = .8 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .8 * sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow window(
      sf::VideoMode(display_width, display_height), "Simulatore di Pandemia",
      sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

  // entity sarà alla base di ogni cella proiettata a schermo
  sf::RectangleShape entity;
  float delta = .6 * sf::VideoMode::getDesktopMode().height / n;
  entity.setSize(sf::Vector2f(delta, delta));
  entity.setFillColor(sf::Color::Green);
  entity.setOutlineColor(sf::Color::Black);

  // base è lo sfondo nero dietro le celle e quello giallo dietro ai dati
  sf::RectangleShape base;

  /*text_display conterrà il testo da proiettare, qui ne definiamo le
   * caratteristiche generiche*/
  sf::Font font;
  font.loadFromFile("arial.ttf");

  sf::Text text_display;
  text_display.setFont(font);
  text_display.setCharacterSize(26);
  text_display.setFillColor(sf::Color::Black);

  // il testo della legenda non cambia, quindi lo definiamo fuori dal loop
  sf::Text legend_display;
  legend_display.setFont(font);
  legend_display.setCharacterSize(20);
  legend_display.setFillColor(sf::Color(54, 54, 54));
  legend_display.setString(
      "INVIO: aggiorna \nQ: attiva/disattiva quarantena\nS:sovrascrive i "
      "dati del SIR");
  legend_display.setPosition(display_width * 0.55, display_height * 0.83);

  // qui inizializzo data usando il costruttore di Sir_Model
  SirModel data(infect, deadly, heal, n, world.countState(0),
                world.countState(1));
  data.generateStandardOutput(world.getDay());

  // inizia il game loop
  while (window.isOpen()) {
    // pool degli eventi
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyReleased:
          eventManager(event.key.code, world, data);
          break;

        default:
          break;
      }
    }

    // ora ripassiamo i dati in people dove saranno usati per la grafica
    // people_update serve proprio a distinguere 2 diversi cicli, se no i primi
    // cambiamenti influenzano i successivi
    world.saveUpdates();

    // inizia la parte grafica, cancello il vecchio frame e preparo lo sfondo
    window.clear(sf::Color::White);

    // imposto a base le specifiche dello sfondo nero
    base.setSize(
        sf::Vector2f(n * delta + 50 + 50 / n, n * delta + 50 + 50 / n));
    base.setFillColor(sf::Color::Black);
    base.setOutlineColor(sf::Color::Black);
    base.setOutlineThickness(0.f);
    base.setPosition(50 - 50 / n, 50 - 50 / n);
    window.draw(base);

    // procede a disegnare le diverse celle: prima ne determina le
    // caratteristiche poi le disegna (eseguiamo anche un conteggio dei
    // sani/malati/morti)
    for (int i = 1; i < n + 1; i++) {
      for (int j = 1; j < n + 1; j++) {
        entity.setPosition(50 + (j - 1) * (delta + 50.f / n),
                           50 + (i - 1) * (delta + 50.f / n));

        switch (world.getElementState(i, j)) {
          case 0:
            entity.setFillColor(sf::Color::Green);
            break;
          case 1:
            entity.setFillColor(sf::Color::Red);
            break;
          case 2:
            entity.setFillColor(sf::Color::Yellow);
            break;
          case 3:
            entity.setFillColor(sf::Color::Blue);
            break;
          case 4:
            entity.setFillColor(sf::Color::Black);
            break;
          default:
            break;
        }

        if (world.getElementQuarantine(i, j)) {
          entity.setOutlineThickness(-100.f / n);
        } else {
          entity.setOutlineThickness(0.f);
        }

        window.draw(entity);
      }
    }

    // stampiamo a schermi i giorni passati
    std::stringstream text;
    text << "Giorno " << world.getDay();
    text_display.setString(text.str());
    text_display.setPosition(display_width * 0.7, display_height * 0.03);
    window.draw(text_display);

    // modifichiamo base in modo che funga da sfondo per i dati (giallo)
    base.setSize(sf::Vector2f(display_width * 0.45, display_height * 0.45));
    base.setFillColor(sf::Color(240, 220, 140));
    base.setOutlineThickness(2.f);
    base.setPosition(display_width * 0.53, display_height * 0.1);
    window.draw(base);

    // Chiediamo a world di creare la stringa che conterrà le percentuali della
    // simulazione...
    text = world.generateText();
    text_display.setString(text.str());
    text_display.setPosition(display_width * 0.55, display_height * 0.13);
    window.draw(text_display);

    // dopodichè facciamo lo stesso con i dati ottenuti dal modello SIR
    text = data.generateText();
    text_display.setString(text.str());
    text_display.setPosition(display_width * 0.55, display_height * 0.33);
    window.draw(text_display);

    // disegnamo la legenda
    window.draw(legend_display);

    // stampiamo tutto a schermo
    window.display();
  }
  // finisce il game loop

  world.clearPopulation();

  // termina l'applicazione
  return 0;
}