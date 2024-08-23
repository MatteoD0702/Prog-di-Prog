#include "population.hpp"


void Population::init_population(int dim, double starting_percentage, double inf, double dead, double heal, int imm_p)
{
    dimension = dim;

    for(int i=0; i<dim+2; i++){

        /* temporary_row conterrà gli state generati da start per ogni ciclo */
        vector<Person> temporary_row;

        for(int j=0; j<dim+2; j++){

            /* 
            la cornice sarà inizializzata come sana e non sarà mai più considerata,
            le altre celle invece saranno inizializzate casualmente secondo strating_percentage
            */
            Person temporary_element;
            if(i==0 or i==dim+1 or j==0 or j==dim+1){
                temporary_element.start(0);
                temporary_row.push_back(temporary_element);
            }  
            else{
                temporary_element.start(starting_percentage);
                temporary_row.push_back(temporary_element);
            }  
        }
        people.push_back(temporary_row); 
        people_updated.push_back(temporary_row); 
    }

    /* inizializziamo la nostra malattia con init_variables di Desease */
    plague.init_variables(inf, dead, heal, imm_p);   
}


int Population::GetElementState(int i, int j)
{
    return people[i][j].GetState();
}


bool Population::GetElementQuarantine(int i, int j)
{
    return people[i][j].GetQuarantine();
}


void Population::Event_Manager(sf::Event event)
{
    //quando viene premuto invio la mia simulazione deve evolversi
    if(event.key.code == sf::Keyboard::Enter){
        for(int i=1; i<dimension+1; i++){
            for(int j=1; j<dimension+1; j++){
                switch(people[i][j].GetState()){
                    /*
                    la cella è sana, può quindi essere infettata dai vicini tramite infection,
                    non c'è bisogno di escludere per k=i e z=j perchè siamo nel case in cui ij è sana (non si può infettare da sola se è sana)
                    */
                    case 0: 
                        for(int k=i-1; k<=i+1; k++){
                            for(int z=j-1; z<=j+1; z++){
                                if(people[k][z].GetState() == 1 && people[k][z].GetQuarantine() == 0){
                                    people_updated[i][j].infection(plague.GetInfect()); 
                                }
                            }
                        }
                    break;

                    /*la cella è malata, potrebbe morire o, nel caso non accadesse potrebbe guarire*/
                    case 1: 
                    people_updated[i][j].destiny(plague.GetDeadly(), plague.GetHeal());  
                    break;

                    case 2: //la cella è guarita da poco, non può essere infettata. L'immunità è solo temporanea (se immunity_time < immunity_period) 
                    people_updated[i][j].immunity_check(people[i][j].GetImmu_Time() , plague.GetPeriod());
                    break;

                    case 3: break; //la cella è vaccinata, non può più essere infettata

                    case 4: break; //la cella è morta e deve rimanere tale

                    default: break;
                }
            }
        }
        day++;
    }
    
    /*quando viene premuta la Q le celle malate devono finire in quarantena*/
    if(event.key.code == sf::Keyboard::Q){
        for(int i=1; i<dimension+1; i++){
            for(int j=1; j<dimension+1; j++){
                if(people[i][j].GetState() == 1){people_updated[i][j].SetQuarantine(true);}
            }
        }
    }

    /*quando viene premuta la F tutte le celle ancora in quarantena vengono liberate*/
    if(event.key.code == sf::Keyboard::F){
        for(int i=1; i<dimension+1; i++){
            for(int j=1; j<dimension+1; j++){
                if(people[i][j].GetQuarantine()){people_updated[i][j].SetQuarantine(false);}
            }
        }           
    }
}

void Population::Confirm()
{
    for(int i=1; i<dimension+1; i++){
        for(int j=1; j<dimension+1; j++){
            people[i][j].init_variables(people_updated[i][j]);
        }
    }    
}

double Population::CountState(int state)
{   
    int count=0;

    for(int i=1; i<dimension+1; i++){
        for(int j=1; j<dimension+1; j++){ 
            if(state == people[i][j].GetState()){count++;}
        }
    }  

    return count;
}

int Population::GetDay()
{
    return day;
}

std::stringstream Population::Generate_Text()
{ 
    std::stringstream text;
    text<<std::fixed<<std::setprecision(2)
        <<"Risultati della Simulazione: \n"
        <<"Sani: "<< 100*CountState(0)/(dimension*dimension) <<"%\n"
        <<"Infetti: "<< 100*CountState(1)/(dimension*dimension) <<"%\n"
        <<"Rimossi: "<< 100*(CountState(2) + CountState(4))/(dimension*dimension) <<"%\n";
    return text;
}


