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
    
    string dossier=nom_fichier + "_out";
    stringstream command;
    command << "mkdir " << nom_fichier << "_out";

    if(mkdir(command.str().c_str(), 0777)){}

    cout << "Etat initial" << endl;
    ShowStat();

    int count=0;
    while (is_running)
    {

        if(verif)
        {
            if(VerifDiff())
            {
                cout << "---\nPlus auccune évolution\n---" << endl;
                break;
            }

            stat_grille=main_grille.GetGrille();

        }

        verif=!verif;


        

        stringstream path;
        path << dossier<< "/" << "Iterration_" << count;
        ofstream fichier(path.str().c_str());
        if(fichier.is_open())
        {
            vector<vector<Cellule>> Cellules=main_grille.GetGrille();
            for(int y=0; y<main_grille.GetHauteur(); y++)
    {
                for(int x=0; x<main_grille.GetLargeur(); x++)
                {
                    if(Cellules[y][x].isObstacle()) {
                        fichier << 2;
                    }else if(Cellules[y][x].isVivante()){
                        fichier << 1;
                    }else if(!Cellules[y][x].isVivante()){
                        fichier << 0;
                    }
                }
                fichier << endl;
            }
        }

        if(count==itteration) {
            cout << "Interuption" << endl;
            break;
        }

        main_grille.mettreAJour();
        count++;
    }

    cout << "Etat final" << endl;
    ShowStat();
    
}