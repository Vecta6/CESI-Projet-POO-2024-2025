#include "grille.hpp"
#include <iostream>
#include <fstream>

using namespace std;


Grille::Grille(int largeur, int hauteur, int tailleCellule)
    : largeur(largeur), hauteur(hauteur), tailleCellule(tailleCellule) {
    cellules.resize(hauteur, std::vector<Cellule>(largeur));
}

int Grille::initialiserGrille(string file) {


    if(file!="")
    {
        ifstream Fichier(file);
        if(!Fichier){
            cerr << "Impossible d'ouvrir le fichier" << endl;
            return 1;
        }

    } else {
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                cellules[i][j].setVivante(rand() % 2);
            }
        }
    }

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
            
            if (cellules[ni][nj].isVivante()) {
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