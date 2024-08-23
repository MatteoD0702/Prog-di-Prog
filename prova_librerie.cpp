#include "Sir_model.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>

#include <iostream>

/* 
  g++ prova_librerie.cpp Sir_model.cpp population.cpp person.cpp desease.cpp -lsfml-graphics -lsfml-window -lsfml-system -Wall -Wextra -fsanitize=address 
*/


double Check_Percentage(){
  double perc;
  std::cin>>perc;

  if(perc<0 or perc>100){
    std::cout<<"percentuale non valida (i valori devono essere compresi tra 0 e 100), riprova:"<<"\n";
    return Check_Percentage();
  }
  return perc;
}


int main() {

  // inizializziamo srand
  std::srand(static_cast<unsigned>(time(NULL)));

  /*saranno la dimensione dell'array n*n e la probabilità di essere malato fin dall'inizio*/
  int n; double starting_percentage;    

  std::cout<<"inserisci la dimensione della popolazione (il numero delle persone sarà n^2)"<<"\n";
  std::cin>>n;
  while(n<=0) {
    std::cout<<"valore non valido (la dimensione deve essere maggiore di 0), riprova:"<<"\n";
    std::cin>>n;
  }
  std::cout<<"inserisci la percentuale di popolazione già infetta (es. 10)"<<"\n";
  starting_percentage=Check_Percentage();
  
  // le variabili utili a inizializzare la malattia
  double infect; double deadly; double heal; int immunity;  

  std::cout<<"inserisci il tasso di infezione, cioe' la probabilità che una persona infetti un vicino (es. 30)"<<"\n";
  infect=Check_Percentage();
  std::cout<<"inserisci il tasso di mortalità, cioe' la probabilità che una persona infetta muoia (es. 20)"<<"\n";
  deadly=Check_Percentage();
  std::cout<<"inserisci il tasso di guarigione, cioe'la probabilità che una persona infetta guarisca (es. 25)"<<"\n";
  heal=Check_Percentage();
  std::cout<<"inserisci il periodo di immunita' post-guarigione, cioè il numero di giorni di immunita' (es. 4)"<<"\n";
  std::cin>>immunity;
  while(immunity<0) {
    std::cout<<"valore non valido (il numero di giorni deve essere maggiore o uguale a zero), riprova:"<<"\n";
    std::cin>>immunity;
  }

  Population world;
  world.init_population(n, starting_percentage, infect, deadly, heal, immunity);

  /*definiamo le specifiche della finestra*/
  unsigned const display_width = .8 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .8 * sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow window(sf::VideoMode(display_width, display_height),"Simulatore di Pandemia", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

  //entity sarà alla base di ogni cella proiettata a schermo
  sf::RectangleShape entity;
  float delta = .6 * sf::VideoMode::getDesktopMode().height/n;
  entity.setSize(sf::Vector2f(delta , delta));
  entity.setFillColor(sf::Color::Green);
  entity.setOutlineColor(sf::Color::Black);

  //base è lo sfondo nero dietro le celle e quello giallo dietro ai dati
  sf::RectangleShape base;
  

  /*text_display conterrà il testo da proiettare, qui ne definiamo le caratteristiche generiche*/
  sf::Text text_display;
  sf::Font font;
  font.loadFromFile("arial.ttf");
  text_display.setFont(font);
  text_display.setCharacterSize(26);
  text_display.setFillColor(sf::Color::Black);


  //qui inizializzo data usando il costruttore di Sir_Model
  Sir_Model data(infect, deadly, heal, n, world.CountState(0), world.CountState(1));

  // inizia il game loop
  while (window.isOpen()) {
    
    // pool degli eventi
    sf::Event event;
    while (window.pollEvent(event)) {
      switch(event.type){
        case sf::Event::Closed: window.close(); break;

        case sf::Event::KeyReleased:
          world.Event_Manager(event);
          if(event.key.code == sf::Keyboard::Enter){data.Analysis();}
        break;

        default: break;
      }
    }

    //ora ripassiamo i dati in people dove saranno usati per la grafica (people_update serve per distinguere 2 diversi cicli, se no i primi cambiamenti influenzano i successivi)
    world.Confirm();

    //ricontrolliamo gli stati dopo il confirm


    //inizia la parte grafica, cancello il vecchio frame e preparo lo sfondo
    window.clear(sf::Color::White);

    //imposto a base le specifiche dello sfondo nero
    base.setSize(sf::Vector2f(n*delta +50 +50/n , n*delta +50 +50/n));
    base.setFillColor(sf::Color::Black);
    base.setOutlineColor(sf::Color::Black);
    base.setOutlineThickness(0.f);
    base.setPosition(50-50/n, 50-50/n);
    window.draw(base);

    // procede a disegnare le diverse celle: prima ne determina le caratteristiche poi le disegna (eseguiamo anche un conteggio dei sani/malati/morti) 
    for(int i=1; i<n+1; i++){
      for(int j=1; j<n+1; j++){

        entity.setPosition(50+(j-1)*(delta+50.f/n),50+(i-1)*(delta+50.f/n));

        switch(world.GetElementState(i,j)){
          case 0: entity.setFillColor(sf::Color::Green); break;
          case 1: entity.setFillColor(sf::Color::Red); break;              
          case 2: entity.setFillColor(sf::Color::Yellow); break;
          case 3: entity.setFillColor(sf::Color::Blue); break;
          case 4: entity.setFillColor(sf::Color::Black); break;
          default: break;
        }

        if(world.GetElementQuarantine(i,j)){entity.setOutlineThickness(-100.f/n);}
        else{entity.setOutlineThickness(0.f);}

        window.draw(entity);
      }
    }

    //stampiamo a schermi i giorni passati
    std::stringstream text;
    text <<"Giorno "<< world.GetDay();
    text_display.setString(text.str());
    text_display.setPosition(display_width*0.7, display_height*0.03);
    window.draw(text_display);

    //modifichiamo base in modo che funga da sfondo per i dati (giallo camoscio)
    base.setSize(sf::Vector2f(display_width*0.45, display_height*0.45));
    base.setFillColor(sf::Color(240,220,140));
    base.setOutlineThickness(2.f);
    base.setPosition(display_width*0.53, display_height*0.1);
    window.draw(base);

    //Creiamo la stringa che conterrà le percentuali della simulazione...
    text = world.Generate_Text();
    text_display.setString(text.str());
    text_display.setPosition(display_width*0.55, display_height*0.13);
    window.draw(text_display);

    //dopodichè la usiamo anche per i dati ottenuti dal modello SIR
    text = data.Generate_Text();
    text_display.setString(text.str());
    text_display.setPosition(display_width*0.55, display_height*0.33);
    window.draw(text_display);


    window.display();
  }
  // finisce il game loop


  // termina l'applicazione
  return 0;
}