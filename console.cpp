#include "console.hpp"

#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>



using namespace std;


Console::Console(Grille grille) : main_grille(grille) {}




void Console::ShowStat()
{
    // Afficher la grille
    vector<vector<Cellule>> Cellules=main_grille.GetGrille();
    
    for(int y=0; y<main_grille.GetHauteur(); y++)
    {
        for(int x=0; x<main_grille.GetLargeur(); x++)
        {
            if(Cellules[y][x].isVivante() && !Cellules[y][x].isObstacle()) {
                cout << "■ ";
            }else  if(!Cellules[y][x].isVivante() && !Cellules[y][x].isObstacle()){
                cout << "⋅ ";
            }else if(Cellules[y][x].isObstacle()){
                cout << "◻ ";
            }
        }
        cout << endl;
    }
}


bool Console::VerifDiff()
{

    vector<vector<Cellule>> Cellules=main_grille.GetGrille();
    int count=0;
    int total_cellules=main_grille.GetHauteur()*main_grille.GetLargeur();

    for(int y=0; y<main_grille.GetHauteur(); y++)
    {
        for(int x=0; x<main_grille.GetLargeur(); x++)
        {
            if(Cellules[y][x].isVivante()==stat_grille[y][x].isVivante()) {
                count+=1;
            }
        }
    }

    if(count==total_cellules)
    {
        return 1;
    }

    return 0;

}


void Console::execute(string nom_fichier, int itteration=0)
{

    is_running=true;
    bool verif=false;
    stat_grille=main_grille.GetGrille();
    
    // Creation du nom de dossier
    stringstream dossier;
    dossier << nom_fichier << "_out";

    // Creation du dossier
    if(mkdir(dossier.str().c_str(), 0777)){}



    cout << "Etat initial" << endl;
    ShowStat();

    int count=0;
    while (is_running)
    {

        // condition pour qui s'execute une fois sur deux
        if(verif)
        {   
            // si il y a un difference entre les 2 etats alors stopper la boucle
            if(VerifDiff())
            {
                cout << "---\nPlus auccune évolution\n---" << endl;
                break;
            }

            stat_grille=main_grille.GetGrille();

        }

        verif=!verif;


        

        // Enregistrer la grille dans un fichier
        stringstream path;
        path << dossier.str() << "/" << "Iterration_" << count;
        ofstream fichier(path.str().c_str());

        // Verification de la bonne ouvertur du fichier
        if(fichier.is_open())
        {
            vector<vector<Cellule>> Cellules=main_grille.GetGrille();
            for(int y=0; y<main_grille.GetHauteur(); y++)
            {           
                for(int x=0; x<main_grille.GetLargeur(); x++)
                {
                    if(Cellules[y][x].isObstacle()) {
                        fichier << 2 << " ";
                    }else if(Cellules[y][x].isVivante()){
                        fichier << 1 << " ";
                    }else if(!Cellules[y][x].isVivante()){
                        fichier << 0 << " ";
                    }
                }
                fichier << endl;
            }
        }


        // si un nombre d'itteration a était entré alors faire en sorte que quand ça arrive au nombre d'itteration cible, arreter la boucle
        if(count==itteration && itteration>0) {
            cout << "Interuption" << endl;
            break;
        }

        // mise a jour de la grille pour passer la 'iterration suivante
        main_grille.mettreAJour();
        count++;
    }

    cout << "Etat final" << endl;
    ShowStat();
    
}




Console::~Console(){}