#include "grille.hpp"
#include <iostream>
#include <fstream>
#include <optional>

using namespace std;


Grille::Grille(int largeur, int hauteur, int tailleCellule)
    : largeur(largeur), hauteur(hauteur), tailleCellule(tailleCellule) {
    cellules.resize(hauteur, std::vector<Cellule>(largeur));
}

int Grille::initialiserGrille(const vector<vector<string>> table) {


    if(!table.empty())
    {

        int y_size=table.size()-1;

        
        for(int y=0; y<hauteur; y++)
        {
            int x_size=table[y].size()-1;

            for(int x=0; x<largeur; x++)
            {
                if(y>y_size || x>x_size)
                {
                    cellules[y][x].setVivante(false);
                }else if (table[y][x]=="2")
                {
                    cellules[y][x].setObstacle(true);

                } else if (table[y][x]=="1")
                {
                    cellules[y][x].setVivante(true);

                }else if(table[y][x]=="0")
                {
                    cellules[y][x].setVivante(false);

                }
            }
        }


    } else {
        srand(time(NULL));
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                cellules[i][j].setVivante(rand() % 2);
            }
        }
    }
    initialstate = cellules;

    return 0;
}

vector<vector<Cellule>> Grille::GetGrille() {
    return cellules;
}

int Grille::compterVoisinsVivants(int x, int y) {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int ni = (x + i + hauteur) % hauteur;
            int nj = (y + j + largeur) % largeur;
            
            if (cellules[ni][nj].isVivante() && !cellules[ni][nj].isObstacle()) {
                voisinsVivants++;
            }
        }
    }
    return voisinsVivants;
}

void Grille::mettreAJour() {
    vector<vector<Cellule>> nouvelleGrille = cellules;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if(nouvelleGrille[i][j].isObstacle()){continue;}
            int voisinsVivants = compterVoisinsVivants(i, j);

            if (cellules[i][j].isVivante()) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    nouvelleGrille[i][j].setVivante(false);  // La cellule meurt
                }
            } else {
                if (voisinsVivants == 3) {
                    nouvelleGrille[i][j].setVivante(true);  // La cellule naît
                }
            }
        }
    }

    cellules = nouvelleGrille;
}




int Grille::GetLargeur()
{
    return largeur;
}

int Grille::GetHauteur()
{
    return hauteur;
}

int Grille::GetTailleCellule()
{
    return tailleCellule;
}

void Grille::reset() {
    cellules = initialstate;
}







Grille::~Grille(){}