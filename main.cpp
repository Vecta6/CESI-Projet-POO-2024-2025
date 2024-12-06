#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>
using namespace std;

#include "grille.hpp"
#include "cellule.hpp"
#include "interface.hpp"

const int cellSize = 5;
int gridWidth = 15;
int gridHeight = 15;



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

    vector<vector<string>> table;

    if(fichier!="")
    {
        ifstream file(fichier);
        if(!file.is_open())
        {  
            cerr << "Impossible d'ouvrir le fichier" <<  endl;
            return 2;
        }

        string ligne;

        getline(file, ligne);
        istringstream stream(ligne);
        string mot;

        stream >> mot;
        gridHeight=stoi(mot);

        stream >> mot;
        gridWidth=stoi(mot);



        while (getline(file, ligne))
        {
            istringstream stream(ligne);
            vector<string> mots;
            string mot;

            while (stream >> mot)
            {
                cout << mot;
                mots.insert(mots.end(), mot);
            }

            cout << endl;
            
            table.insert(table.end(), mots);
            
        }
        file.close();
    }


    Grille grille(gridWidth, gridHeight, cellSize);

    if(reponse==1)
    {


        grille.initialiserGrille(table);
        

        bool isRunning=true;
        while (isRunning)
        {
            // Afficher la grille
            vector<vector<Cellule>> Cellules=grille.GetGrille();
            
            cout << "----" << endl;
            for(int y=0; y<gridHeight; y++)
            {
                for(int x=0; x<gridWidth; x++)
                {
                    if (Cellules[y][x].isObstacle())
                    {
                        cout << "◻ ";
                    }else if(Cellules[y][x].isVivante()==1) {
                        cout << "■ ";
                    }else  if(Cellules[y][x].isVivante()==0){
                        cout << "⋅ ";
                    }

                }
                cout << endl;
            }

            usleep(100 * 1000);
            grille.mettreAJour();
            
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
