#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <typeinfo>

#include <iostream>
using namespace std;

#include "grille.h"
#include "cellule.h"
#include "interface.h"

const int cellSize = 5;
const int gridWidth = 200;
const int gridHeight = 200;



int prompt()
{
    int reponse=0;
    system("clear");
    cout << "Bienvenu dans le jeu de la vie\n" << endl;
    
    do {
        cout << "Choisissez un mode : \n(1) Mode Console\n(2) Mode Graphique" << endl;
        cin >> reponse;
        reponse=int(reponse);
        
    } while (reponse!=1 && reponse!=2);

    return reponse;
    
}



int main(int argc, char *argv[], char *envp[]) {
    

    if(argc>1)
    {
        cout << "Les parametres ne sont pas encore pris en charge" << endl;
        // for(int i=1; i<argc; i++)
        // {
        //     cout << argv[i] << endl ;
        // }
    }


    



    int reponse=prompt();

    if(reponse==1)
    {
        cout << "Pas encore disponible" << endl;
        Grille grille(gridWidth, gridHeight, cellSize);

        grille.initialiserGrille();




    }else if(reponse==2){
        // sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Jeu de la vie");
        // while (window.isOpen())
        // {
        //     sf::Event event;
        //     while (window.pollEvent(event)) {
        //         if (event.type == sf::Event::Closed)
        //             window.close();
        //     }


        //     grille.afficher(window);

        //     grille.mettreAJour();

        //     sf::sleep(sf::milliseconds(10));
        // }

        try {
            InterfaceGraphique interface(gridWidth, gridHeight, cellSize);
            interface.executer();
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << std::endl;
        }
    }


    
    

    return 0;
}
