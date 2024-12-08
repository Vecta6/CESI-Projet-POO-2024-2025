#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

#include "grille.hpp"
#include "cellule.hpp"
#include "interface.hpp"
#include "console.hpp"

const int cellSize = 10;
int gridWidth = 55;
int gridHeight = 55;



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
    int itteration=0;



    // recuperer les different argument
    if(argc>1)
    {
        for(int i=1; i<argc; i++)
        {
            if(string(argv[i])=="-f" && argv[i+1])
            {
                fichier=string(argv[i+1]);
            } else if (string(argv[i])=="-i" && argv[i+1]) {
                itteration=stoi(argv[i+1]);
            }
        }
    }






    // Transformer le fichier selectionné en tableau
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
                mots.insert(mots.end(), mot);
            }
            
            table.insert(table.end(), mots);
            
        }
        file.close();
    }


    // Interoger l'utilisateur
    int reponse=prompt();

    // Initialiser la grille
    Grille grille(gridWidth, gridHeight, cellSize);
    grille.initialiserGrille(table);

    // mode conole ou mode graphique
    if(reponse==1)
    {
        Console console(grille);

        
        size_t pos = fichier.find_last_of("/\\");
        fichier=fichier.substr(pos+1);

    
        
        console.execute(fichier, itteration);
        
        

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
