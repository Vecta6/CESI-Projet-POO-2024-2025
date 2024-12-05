#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "grille.hpp"
#include "cellule.hpp"
#include "interface.hpp"

const int cellSize = 5;
const int gridWidth = 150;
const int gridHeight = 100;



int prompt()
{
    int reponse=0;
    cout << "Bienvenu dans le jeu de la vie\n" << endl;
    
    do {
        cout << "Choisissez un mode : \n(1) Mode Console\n(2) Mode Graphique" << endl;
        cin >> reponse;
        reponse=int(reponse);
        
    } while (reponse!=1 && reponse!=2);

    return reponse;
    
}



int main(int argc, char *argv[], char *envp[]) {
    
    string fichier;

    if(argc>1)
    {
        for(int i=1; i<argc; i++)
        {
            if(string(argv[i])=="-f" && argv[i+1])
            {
                fichier=string(argv[i+1]);
            }
        }
    }

    int reponse=prompt();

    Grille grille(gridWidth, gridHeight, cellSize);

    if(reponse==1)
    {


        grille.initialiserGrille(fichier);
        

        bool isRunning=true;
        while (isRunning)
        {
            
        }
        

    }else if(reponse==2){

        try {
            InterfaceGraphique interface(grille);
            interface.executer();
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << std::endl;
        }

    }



    return 0;
}
